#pragma once

#include <grpcpp/grpcpp.h>
#include "grpc/state/state.grpc.pb.h"

class StateServerRpcServiceImpl final : public State::Service
{
public:
    /// @brief gateway发来取消连接（也就是客户端断开连接）的信令时的处理逻辑，是rpc方法的具体实现
    /// @param request 
    /// @param response 
    /// @param ctx 
    grpc::Status CancelConn(grpc::ServerContext* context, const StateRequest* request, StateResponse *response) override;

    /// @brief gateway发来给某个用户转发消息的信令时的处理逻辑，是rpc方法的具体实现
    /// @param request 
    /// @param response 
    /// @param ctx 
    grpc::Status SendMsg(grpc::ServerContext* context, const StateRequest* request, StateResponse *response) override; 
};