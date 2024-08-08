#include "messagesender.h"
#include "rpc/client/routercaller.h"
#include <vector>
#include <string>
#include <spdlog/spdlog.h>

MessageSender &MessageSender::Get()
{
    static MessageSender sender;
    return sender;
}

void MessageSender::PushMessage(uint64_t session_id, message::CmdType cmd_type, std::string content)
{
    // 先查sessionID到对应的userID，这个查缓存，但是key啥的得看会话层的设计，这里先留空，后面补上
    // 也就是说这里其实应该去会话域查询userID，而不是去router server
    // 。。。。
    std::vector<uint64_t> user_id_list;

    // 由于router server能做到userID到endpoint的映射，所以消息直接发给router server，由router server帮我们发给对应的网关机即可
    message::MsgCmd msg_cmd;
    msg_cmd.set_type(cmd_type);
    msg_cmd.set_payload(content);

    std::string msg_cmd_str;
    if (!msg_cmd.SerializeToString(&msg_cmd_str))
    {
        spdlog::error("MessageSender.cc::PushMessage: Serialize msg_cmd failed!");
        return;
    }
    
    for (auto& user_id : user_id_list)
    {
        RouterCaller::Get().PushMessage(user_id, msg_cmd_str);
    }
}

void MessageSender::FanoutMessage(message::CmdType cmd_type, std::string content)
{
    message::MsgCmd msg_cmd;
    msg_cmd.set_type(cmd_type);
    msg_cmd.set_payload(content);

    std::string msg_cmd_str;
    if (!msg_cmd.SerializeToString(&msg_cmd_str))
    {
        spdlog::error("MessageSender.cc::FanoutMessage: Serialize msg_cmd failed!");
        return;
    }

    RouterCaller::Get().FanoutMessage(msg_cmd_str);
}
