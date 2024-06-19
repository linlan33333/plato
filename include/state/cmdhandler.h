#pragma once

#include "grpc/state/cmdcontext.h"
#include "idl/message/message.pb.h"
#include "cache.h"
#include <map>
#include <functional>

using MsgHandler = std::function<void(CmdContext&, message::MsgCmd&)>;

class CmdHandler
{
public:
    static CmdHandler& Get();

    MsgHandler GetHandler(message::CmdType type);

    /// @brief 该接口会完成反序列化网关发来的message数据，自动识别信令类型，然后调用相应的handler函数三个步骤
    /// @param message 
    void MsgCmdHandler(CmdContext& cmdctx);

    // 消息重发函数，该函数会递归地包装成定时器函数实现无限重发，所以需要单独封装
    // ConnectionState中消息重发定时器需要设置定时执行该函数，而且CacheState中的ConnReLogin函数也可能
    // 需要使用该函数，所以把该函数拎出来暴露给外部使用，如果有更好的办法再做修改
    void RePush(uint64_t connid);

    /// @brief 消息发送函数，由业务层IM server调用，负责将下行消息发送到该用户手中，同时存储消息到redis飞行队列中
    /// @param connid 
    /// @param sessionid 
    /// @param msgid 
    /// @param data 
    void PushMsg(uint64_t connid, uint64_t sessionid, uint64_t msgid, const std::string& content);

private:
    CmdHandler();

    CmdHandler(const CmdHandler&) = delete;
    CmdHandler& operator= (const CmdHandler&) = delete;

    /// @brief 见名知意
    /// @param ctx 未反序列化信令之前的原始数据信息
    /// @param cmd 信令
    void LoginMsgHandler(CmdContext& ctx, message::MsgCmd& cmd);
    void HeartBeatMsgHandler(CmdContext& ctx, message::MsgCmd& cmd);
    void ReConnMsgHandler(CmdContext& ctx, message::MsgCmd& cmd);
    // 上行消息的处理逻辑，上行消息指的是客户端发送消息给我
    void UpMsgHandler(CmdContext& ctx, message::MsgCmd& cmd);
    // 下行消息的处理逻辑，下行消息指的是我推送消息给客户端，客户端收到后回复的ACK消息
    void AckMsgHandler(CmdContext& ctx, message::MsgCmd& cmd);

    /// 多个地方通用的方法
    void SendAckMsg(message::CmdType cmd_type, uint64_t connid, uint64_t clientid, uint32_t code, std::string msg);
    void SendMsg(uint64_t connid, message::CmdType cmd_type, std::string& download);

    std::map<int, MsgHandler> msg_handler_map_;
};