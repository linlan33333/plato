#include "cmdhandler.h"
#include "state/timer.h"
#include "cache.h"
#include "rpc/client/gatewaycaller.h"
#include "idl/message/message.pb.h"
#include <spdlog/spdlog.h>

CmdHandler &CmdHandler::Get()
{
    static CmdHandler handler;
    return handler;
}

MsgHandler CmdHandler::GetHandler(message::CmdType type)
{
    auto msg_handler_pair = msg_handler_map_.find(type);
    if (msg_handler_pair != msg_handler_map_.end()) 
    {
        return msg_handler_pair->second;
    }

    // 返回个空的临时对象
    return MsgHandler ();
}

void CmdHandler::MsgCmdHandler(CmdContext& cmd_ctx)
{
    message::MsgCmd msg_cmd;
    if (!msg_cmd.ParseFromString(cmd_ctx.Payload))
    {
        spdlog::warn("CmdHandler.cc::MsgCmdHandler: Parse message from string failed!");
        return;
    }

    message::CmdType type = msg_cmd.type();
    // 调用相应的handler函数处理
    GetHandler(type)(cmd_ctx, msg_cmd);
}

CmdHandler::CmdHandler()
{
    msg_handler_map_.insert({message::CmdType::Login, std::bind(&CmdHandler::LoginMsgHandler, this, std::placeholders::_1, std::placeholders::_2)});
    msg_handler_map_.insert({message::CmdType::Heartbeat, std::bind(&CmdHandler::HeartBeatMsgHandler, this, std::placeholders::_1, std::placeholders::_2)});
    msg_handler_map_.insert({message::CmdType::ReConn, std::bind(&CmdHandler::ReConnMsgHandler, this, std::placeholders::_1, std::placeholders::_2)});
    msg_handler_map_.insert({message::CmdType::UP, std::bind(&CmdHandler::UpMsgHandler, this, std::placeholders::_1, std::placeholders::_2)});
    msg_handler_map_.insert({message::CmdType::ACK, std::bind(&CmdHandler::AckMsgHandler, this, std::placeholders::_1, std::placeholders::_2)});
}

void CmdHandler::LoginMsgHandler(CmdContext& ctx, message::MsgCmd& cmd)
{
    message::LoginMsg login_msg;
    std::string msg_str = cmd.payload();
    if (!login_msg.ParseFromString(msg_str))
    {
        spdlog::warn("CmdHandler.cc::LoginMsgHandler: Parse from string error!");
        return;
    }

    // 这里处理业务逻辑，将消息发给业务层进行下一步
    // 。。。。。。
    std::cout << "恭喜你登录成功" << std::endl;

    // 这一步完成创建ConnectionState、存储该用户的连接状态、设置心跳定时器等操作
    CacheState::Get().ConnLogin(login_msg.head().deviceid(), ctx.ConnID);

    // 回复客户端登录成功
    SendAckMsg(message::Login, ctx.ConnID, 0, 0, "login ok");
}

void CmdHandler::HeartBeatMsgHandler(CmdContext& ctx, message::MsgCmd& cmd)
{
    message::HeartbeatMsg msg;
    std::string msg_str = cmd.payload();
    if (!msg.ParseFromString(msg_str))
    {
        spdlog::warn("CmdHandler.cc::HeartBeatMsgHandler: Parse from string error!");
        return;
    }

    // 重置心跳定时器
    std::shared_ptr<ConnectionState> conn_state = CacheState::Get().GetConnIDState(ctx.ConnID);
    if (conn_state != nullptr) 
    {
        conn_state->ResetHeartBeatTimer();
    }

    // TODO 为减少通信量，可以暂时不回复心跳的ack
}

void CmdHandler::ReConnMsgHandler(CmdContext &ctx, message::MsgCmd &cmd)
{
    message::ReConnMsg msg;
    std::string msg_str = cmd.payload();
    if (!msg.ParseFromString(msg_str))
    {
        spdlog::warn("CmdHandler.cc::ReConnMsgHandler: Parse from string error!");
        return;
    }

    // 重连消息头中的connID才是上一次断开连接的connID
    uint64_t last_connid = msg.head().connid();
    // 删掉redis和router中老的connid信息，注册新的
    if (CacheState::Get().ReConnection(last_connid, ctx.ConnID))
    {
        SendAckMsg(message::ReConn, ctx.ConnID, 0, 0, "reconn ok");
        return;
    }

    // 调用失败，说明没找到老的connid对应的状态，那就说明已经超时被清理了，让客户端重新登录吧
    SendAckMsg(message::ReConn, ctx.ConnID, 0, 1, "reconn failed");
}

void CmdHandler::UpMsgHandler(CmdContext &ctx, message::MsgCmd &cmd)
{
    message::UPMsg up_msg;
    std::string msg_str = cmd.payload();
    if (!up_msg.ParseFromString(msg_str))
    {
        spdlog::warn("CmdHandler.cc::UpMsgHandler: Parse from string error!");
        return;
    }

    // 检查接收到的消息是否是连贯的，如果是那就交付业务服务器去做进一步处理
    if (CacheState::Get().CompareAndIncrClientID(ctx.ConnID, up_msg.head().clientid()))
    {
        std::cout << "收到的消息是：" << up_msg.upmsgbody() << std::endl;
        // 客户端发上行消息过来我就回上行消息过去，要是CmdType设为ACK客户端就分不清这是哪个信令的ACK了
        SendAckMsg(message::CmdType::UP, ctx.ConnID, up_msg.head().clientid(), 0, "recieve msg ok");

        ///////////////////////////// 以下是模拟给用户推送消息，让用户回复ack，来测试下行消息处理器好不好使
        // 将push_msg发送给用户，这个sessionid和msgid瞎填的
        PushMsg(ctx.ConnID, 0, 1, up_msg.upmsgbody());
    }
    // 接收的消息不连贯怎么办，这里先按下不表
    else 
    {
        spdlog::info("CmdHandler.cc::UpMsgHandler: The received message is not coherent");
    }
}

void CmdHandler::AckMsgHandler(CmdContext &ctx, message::MsgCmd &cmd)
{
    message::ACKMsg ack_msg;
    std::string msg_str = cmd.payload();
    if (!ack_msg.ParseFromString(msg_str))
    {
        spdlog::warn("CmdHandler.cc::AckMsgHandler: Parse from string error!");
        return;
    }

    // 客户端回复了ACK，就取消掉该消息的定时器，这里只做测试用，逻辑简化一下
    // 注意客户端是可以合并确认的，只需要发送最后一次服务器推送的消息的ACK即可，这样服务器就知道客户端
    // 收到的消息到哪一条了
    CacheState::Get().AckLastMsg(ack_msg.connid(), ack_msg.sessionid(), ack_msg.msgid());
}

void CmdHandler::SendAckMsg(message::CmdType cmd_type, uint64_t connid, uint64_t clientid, uint32_t code, std::string msg)
{
    message::ACKMsg ack_msg;
    ack_msg.set_code(code);
    ack_msg.set_msg(msg);
    ack_msg.set_connid(connid);
    ack_msg.set_type(message::ACK);
    ack_msg.set_clientid(clientid);

    std::string download;
    if (!ack_msg.SerializeToString(&download))
    {
        spdlog::warn("CmdHandler.cc::SendAckMsg: Serialize to ACKMsg error!");
        return;
    }

    SendMsg(connid, message::ACK, download);
}

// 发送msg，消息必须打包成MsgCmd再发送，接收也是MsgCmd，发送也是MsgCmd才行
void CmdHandler::SendMsg(uint64_t connid, message::CmdType cmd_type, std::string &download)
{
    message::MsgCmd msg_cmd;
    msg_cmd.set_type(cmd_type);
    msg_cmd.set_payload(download);

    std::string data;
    if (!msg_cmd.SerializeToString(&data))
    {
        spdlog::warn("CmdHandler.cc::SendMsg: Serialize to MsgCmd error!");
        return;
    }

    GatewayCaller::Get().Push(connid, data);
}

void CmdHandler::PushMsg(uint64_t connid, uint64_t sessionid, uint64_t msgid, const std::string &content)
{
    message::PushMsg push_msg;
    push_msg.set_msgid(msgid);
    push_msg.set_sessionid(sessionid);
    push_msg.set_content(content);

    std::string data;
    if (!push_msg.SerializeToString(&data))
    {
        spdlog::warn("CmdHandler.cc::PushMsg: Serialize to PushMsg error!");
        return;
    }

    // 发送下行消息给该用户
    SendMsg(connid, message::Push, data);
    // 将消息存储到redis飞行队列中，不管该消息最终能不能送达到用户手上，都需要更新飞行队列中的最新消息
    // 原本以为飞行队列中的新消息是IM server挂上去的，现在看样子不是，是state server在这里挂上去的，如果
    // 最新消息没来得及挂上去state server挂了，那该消息就丢失了，只能等state server恢复后用户发现msgid
    // 跳变自己主动拉取了
    CacheState::Get().AppendLastMsg(connid, push_msg, data);
}

// 这里需要完成获取最新消息、发送消息和重设定时器三个步骤，然后递归地设置定时器任务为该函数，做到无限重发的效果
// 这个函数的逻辑妙就妙在每次执行时都会获取最新的没推送的消息并发送，确保不会重发过时的消息。
void CmdHandler::RePush(uint64_t connid)
{
    // 去redis中的飞行队列拿最新的消息
    std::unique_ptr<message::PushMsg> push_msg_ptr = CacheState::Get().GetLastMsg(connid);
    // 消息已经发送完成，那么就没有最新消息，这里也就是为空
    if (push_msg_ptr == nullptr) 
    {
        return;
    }

    std::string msg_data;
    if (!push_msg_ptr->SerializeToString(&msg_data))
    {
        spdlog::warn("CmdHandler.cc::RePush: Serialize to PushMsg error!");
        return;
    }
    // 消息发送出去
    SendMsg(connid, message::CmdType::Push, msg_data);

    // 每次自己重新去查找有无该连接对象，防止该连接对象都没了还重发个啥
    std::shared_ptr<ConnectionState> conn_state = CacheState::Get().GetConnIDState(connid);
    if (conn_state != nullptr)
    {
        // 设置消息重发定时器，到点时会自动重新执行该函数，拉取最新消息，重设定时器
        // 你可能会有疑问：如果上一次设置的重发定时器对应的消息一直没收到确认，现在IM server又给飞行队列放入了新的消息
        // 现在定时器到点了执行该逻辑会发生什么？由于重新执行该逻辑，拉取了最新的消息，在这次设置定时器之前上一次的消息
        // 还是没确认，那么ResetMsgTimer会修改定时器的msg_timer_lock为本次新消息的元信息，上一次消息的确认即便到了也不会
        // 影响本次最新消息的定时器，如果这次设置定时器之前上一次的消息确认了，那皆大欢喜，这次设置的定时器就是最新消息的定时器
        conn_state->ResetMsgTimer(push_msg_ptr->sessionid(), push_msg_ptr->msgid());
    }
    else
    {
        spdlog::warn("CmdHandler.cc::RePush: Repush message failed! Can\'t find connection state object!");
    }
}
