#include "netservice.h"
#include "config/gateway.h"
#include "tcp/read.h"
#include "rpc/client/statecaller.h"
#include <spdlog/spdlog.h>

NetService::NetService(muduo::net::EventLoop *loop, const muduo::net::InetAddress &listenAddr)
    : server_(loop, listenAddr, GatewayConfig::Get().GetServiceName())
    , loop_(loop)
{
    server_.setConnectionCallback(std::bind(&NetService::onConnection, this, std::placeholders::_1));
    server_.setMessageCallback(std::bind(&NetService::OnMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    server_.setThreadNum(GatewayConfig::Get().GetThreadNumForNetServer());
}

void NetService::CloseConn(CmdContext cmd_context)
{
    // 上写锁
    std::unique_lock<std::shared_mutex> lck(connid_map_mtx_);
    // 去connid的map表中找到连接对象
    auto connid_pair = connid_map_.find(cmd_context.ConnID);
    if (connid_pair != connid_map_.end()) 
    {
        // 关闭连接
        connid_pair->second->get()->shutdown();
        connid_map_.erase(connid_pair);
        return;
    }

    spdlog::warn("gateway/netservice.cc:26: Can\'t find target TcpConnection object! Can\'t delete target connid!");
}

void NetService::SendMsgByCmd(CmdContext cmd_context)
{
    // 上读锁
    std::shared_lock<std::shared_mutex> lck(connid_map_mtx_);
    // 去connid的map表中找到连接对象
    auto connid_pair = connid_map_.find(cmd_context.ConnID);
    if (connid_pair != connid_map_.end()) 
    {
        if (connid_pair->second->get()->disconnected()) 
        {
            spdlog::warn("gateway/netservice.cc:50: The target TcpConnection has disconnected!");
            return;
        }

        // 发送消息
        connid_pair->second->get()->send(cmd_context.Payload);
        return;
    }

    spdlog::warn("gateway/netservice.cc:50: Can\'t find target TcpConnection object! Can\'t send message!");
}

void NetService::Start()
{
    // 启动网络服务器
    server_.start();
}

muduo::net::TcpConnectionPtr *NetService::GetConnById(unsigned long long connid)
{
    std::shared_lock<std::shared_mutex> lck(connid_map_mtx_);
    auto conn_pair = connid_map_.find(connid);
    if (conn_pair == connid_map_.end())
    {
        spdlog::warn("gateway/netservice.cc:58: Can\'t find target TcpConnection object!");
        return nullptr;
    }

    return const_cast<muduo::net::TcpConnectionPtr*>(conn_pair->second);
}

void NetService::OnMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buf, muduo::Timestamp time)
{
    // 组装信令，后续通过RPC调用发给state server
    // std::string data = Read::Get().ReadData(buf);
    // 现在先测试回声数据
    std::string data = buf->retrieveAllAsString();
    std::cout << data << std::endl;

    // 拿到客户端的endpoint
    std::string endpoint = conn.get()->peerAddress().toIpPort();
    StateCaller::Get().SendMsg(endpoint, (unsigned long long)&conn, data);
}

void NetService::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
    if (conn->connected())
    {
        spdlog::info("{0} -> {1} state: 上线", conn->peerAddress().toIpPort(), conn->localAddress().toIpPort());
        // 存储该conn对象，key是它的物理地址，这样就确保只要conn存在，就只有唯一的id对应它
        connid_map_.insert({(unsigned long long)&conn, &conn});
    }
    else
    {
        spdlog::info("{0} -> {1} state: 下线", conn->peerAddress().toIpPort(), conn->localAddress().toIpPort());
        connid_map_.erase((unsigned long long)&conn);
    }
}
