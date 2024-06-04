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

private:
    CmdHandler();

    CmdHandler(const CmdHandler&) = delete;
    CmdHandler& operator= (const CmdHandler&) = delete;

    void LoginMsgHandler(CmdContext& ctx, message::MsgCmd& cmd);
    void HeartBeatMsgHandler(CmdContext& ctx, message::MsgCmd& cmd);
    void ReConnMsgHandler(CmdContext& ctx, message::MsgCmd& cmd);

    /// 多个地方通用的方法
    void SendAckMsg(message::CmdType cmd_type, uint64_t connid, uint64_t clientid, uint32_t code, std::string msg);
    void SendMsg(uint64_t connid, message::CmdType cmd_type, std::string& download);

    std::map<int, MsgHandler> msg_handler_map_;
};