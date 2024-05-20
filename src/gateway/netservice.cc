#include "netservice.h"
#include "config/gateway.h"
#include "tcp/read.h"
#include <spdlog/spdlog.h>

NetService::NetService(muduo::net::EventLoop *loop)
    : server_(loop, muduo::net::InetAddress (GatewayConfig::Get().GetIp(), GatewayConfig::Get().GetPortForNetService()),
        GatewayConfig::Get().GetServiceName(), muduo::net::TcpServer::kReusePort)
    , loop_(loop)
{

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
        connid_pair->second->shutdown();
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
        // 发送消息
        connid_pair->second->send(cmd_context.Payload);
        return;
    }
    spdlog::warn("gateway/netservice.cc:41: Can\'t find target TcpConnection object! Can\'t send message!");
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

    return conn_pair->second;
}

void NetService::OnMessage(const muduo::net::TcpConnectionPtr &conn, muduo::net::Buffer *buf, muduo::Timestamp time)
{
    // 组装信令，后续通过RPC调用发给state server
    std::string data = Read::Get().ReadData(buf);

    
}
