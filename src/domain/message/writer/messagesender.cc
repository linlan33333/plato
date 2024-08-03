#include "messagesender.h"
#include <vector>
#include <string>

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
    // 目前没有实现router server的改造，这里先留空，后面补上
    // 。。。。。
}
