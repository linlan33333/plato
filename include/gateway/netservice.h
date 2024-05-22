#pragma once

#include "srpc/gateway/cmdcontext.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpConnection.h>
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

    muduo::net::TcpConnectionPtr* GetConnById(unsigned long long connid);

private:
    void OnMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time);
    void onConnection(const muduo::net::TcpConnectionPtr& conn);

    muduo::net::TcpServer server_;

    muduo::net::EventLoop* loop_;

    std::map<unsigned long long, const muduo::net::TcpConnectionPtr*> connid_map_;
    std::shared_mutex connid_map_mtx_;
};