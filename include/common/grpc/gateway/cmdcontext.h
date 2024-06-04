#pragma once

#include <string>

enum class CMD
{
    // 取消连接，就是客户端连接断开了，得告诉state server需要执行断开连接的业务操作
    DelConnCmd = 1,
    // 发送消息，就是客户端给网关发送了数据，得告诉state server需要执行发送消息的业务操作
    Push
};

struct CmdContext
{
public:
    CmdContext() : Cmd(CMD::DelConnCmd), ConnID(0) {}

    CMD Cmd;
    uint64_t ConnID;
    std::string Payload;
};