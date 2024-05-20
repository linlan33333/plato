#pragma once

#include "srpc/state/state.pb.h"
#include "srpc/state/state.srpc.h"

using namespace srpc;

class StateServerRpcServiceImpl : public State::Service
{
public:
    /// @brief gateway发来取消连接（也就是客户端断开连接）的信令时的处理逻辑，是rpc方法的具体实现
    /// @param request 
    /// @param response 
    /// @param ctx 
    void CancelConn(StateRequest *request, StateResponse *response, srpc::RPCContext *ctx) override;

    /// @brief gateway发来给某个用户转发消息的信令时的处理逻辑，是rpc方法的具体实现
    /// @param request 
    /// @param response 
    /// @param ctx 
    void SendMsg(StateRequest *request, StateResponse *response, srpc::RPCContext *ctx) override; 
};