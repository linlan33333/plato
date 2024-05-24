#include "netservice.h"
#include "config/gateway.h"
#include "tcp/read.h"
#include "utils/generateid.h"
#include "rpc/client/statecaller.h"
#include "workpool.h"
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
        if (connid_pair->second->disconnected()) 
        {
            spdlog::warn("gateway/netservice.cc:50: The target TcpConnection has disconnected!");
            return;
        }

        // 发送消息
        connid_pair->second->send(cmd_context.Payload);
        return;
    }

    spdlog::warn("gateway/netservice.cc:50: Can\'t find target TcpConnection object! Can\'t send message!");
}

void NetService::Start()
{
    // 启动网络服务器
    server_.start();
}

muduo::net::TcpConnection *NetService::GetConnById(unsigned long long connid)
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
    // std::string data = Read::Get().ReadData(buf);
    // 现在先测试回声数据
    std::string data = buf->retrieveAllAsString();

    // 拿到客户端的endpoint
    std::string endpoint = conn.get()->peerAddress().toIpPort();
    uint64_t connid = boost::any_cast<uint64_t>(conn->getContext());

    StateCaller::Get().SendMsg(endpoint, connid, data);
}

void NetService::onConnection(const muduo::net::TcpConnectionPtr &conn)
{
    if (conn->connected())
    {
        spdlog::info("{0} -> {1} state: 上线", conn->peerAddress().toIpPort(), conn->localAddress().toIpPort());
        // 存储该conn对象，key是工具类生成的id，这样就确保只要conn存在，就只有唯一的id对应它
        uint64_t connid = GenerateId::Get().GetID();
        // muduo库中TcpConnection对象预留了一个字段context_，可以放一些信息，这里存放connid，下次该对象收到消息触发
        // OnMessage回调函数时，就可以从中取出该connid，向state server发起rpc请求时携带过去，回头好找该TcpConnection对象
        std::unique_lock<std::shared_mutex> lck(connid_map_mtx_);
        conn->setContext(connid);
        // 大map映射表存储该连接对象和对应id,..................这个对象压根没存进去，回头来排查原因，
        // 怀疑就是那个万恶的shared_from_this产生的TcpConnection智能指针对象后面析构了，回头想想怎么办
        connid_map_.insert({connid, conn.get()});
    }
    else
    {
        spdlog::info("{0} -> {1} state: 下线", conn->peerAddress().toIpPort(), conn->localAddress().toIpPort());
        // 下线就得通知state server
        // 。。。。。

        // 删掉该连接对象
        std::unique_lock<std::shared_mutex> lck(connid_map_mtx_);
        uint64_t connid = boost::any_cast<uint64_t>(conn->getContext());
        connid_map_.erase(connid);
    }
}
