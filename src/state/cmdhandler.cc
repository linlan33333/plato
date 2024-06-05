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

    // 存储该用户的连接状态
    std::shared_ptr<ConnectionState> conn_state(std::make_shared<ConnectionState>(ctx.ConnID, login_msg.head().deviceid()));
    CacheState::Get().StoreConnIDState(ctx.ConnID, conn_state);
    
    // 设置心跳定时器，期间没有心跳消息则登出
    uint32_t timer_id = Timer::Get().RunAfter(3 * 1000, std::bind(&CacheState::ConnLogOut, &(CacheState::Get()), ctx.ConnID));
    conn_state->SetHeartTimerId(timer_id);

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
    // 找到原来的ConnectionState
    std::shared_ptr<ConnectionState> conn_state = CacheState::Get().GetConnIDState(last_connid);
    if (conn_state != nullptr) 
    {
        // 先停止重连定时器，都已经触发重连定时器了，说明心跳定时器早执行完了
        // 那心跳定时器咋不设置呢？因为客户端会发送心跳消息，当收到心跳消息时自动重置心跳定时器
        // 那如果客户端发送重连信令后又断开连接了呢？这个情况下该怎么办？
        // 所以个人认为这里就得重新设置一下心跳计时器，客户端不发心跳就清理资源
        conn_state->DeleteReConnTimer();
        conn_state->ResetHeartBeatTimer();
        // 得给conn_state更换connid了
        CacheState::Get().DeleteConnIDState(last_connid);
        CacheState::Get().StoreConnIDState(ctx.ConnID, conn_state);

        SendAckMsg(message::ReConn, ctx.ConnID, 0, 0, "reconn ok");
    }

    // 没找到这个状态，那就说明已经被清理了，重连失败，让客户端重新登录吧
    SendAckMsg(message::ReConn, ctx.ConnID, 0, 1, "reconn failed");
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
