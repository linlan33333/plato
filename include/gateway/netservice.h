#pragma once

#include "grpc/gateway/cmdcontext.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <map>
#include <shared_mutex>

class NetService
{
public:
    NetService() = default;
    NetService(muduo::net::EventLoop* loop, const muduo::net::InetAddress &listenAddr);

    /// @brief 当接到state server发来的删除连接del信令时，会执行该业务函数
    /// @param cmd_context 
    void CloseConn(CmdContext cmd_context);

    /// @brief 当接到state server发来的发送消息push信令时，执行该业务函数
    /// @param cmd_context 
    void SendMsgByCmd(CmdContext cmd_context);

    /// @brief 启动gateway的网络服务器
    void Start();

    muduo::net::TcpConnection* GetConnById(unsigned long long connid);

private:
    void OnMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time);
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    muduo::net::TcpServer server_;

    muduo::net::EventLoop* loop_;

    // key是muduo::net::TcpConnection的地址，value是muduo::net::TcpConnection的指针
    std::map<unsigned long long, muduo::net::TcpConnection*> connid_map_;
    std::shared_mutex connid_map_mtx_;
};