#pragma once

#include <string>

enum class CMD
{
    // 取消连接，就是客户端连接断开了，得告诉state server需要执行断开连接的业务操作
    CancelConnCmd = 1,
    // 发送消息，就是客户端给网关发送了数据，得告诉state server需要执行发送消息的业务操作
    SendMsgCmd
};

struct CmdContext
{
public:
    CmdContext() : Cmd(CMD::CancelConnCmd), ConnID(0) {}

    CMD Cmd;
    int ConnID;
    std::string Payload;
};