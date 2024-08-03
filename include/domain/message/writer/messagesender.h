#pragma once

#include "common/idl/message/message.pb.h"
#include <string>

class MessageSender
{
public:
    static MessageSender& Get();

    /// @brief 这是个异步发送消息的接口，用于对单聊/小群聊进行c2c的rpc推送消息
    /// @param session_id 
    /// @param cmd_type 
    /// @param content 
    void PushMessage(uint64_t session_id, message::CmdType cmd_type, std::string content);

    /// @brief 用于超大群聊消息扇出，底层直接调用router server，发送协议升降级消息也是调用这个接口发送
    /// @param session_id 
    /// @param cmd_type 
    /// @param content 
    void FanoutMessage(uint64_t session_id, message::CmdType cmd_type, std::string content);

private:
    MessageSender() = default;
    MessageSender(const MessageSender&) = delete;
    MessageSender& operator=(const MessageSender&) = delete;
};