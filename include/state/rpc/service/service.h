#pragma once

#include "state/rpc/service/impl.h"
#include "grpc/state/state.grpc.pb.h"

class StateRpcService
{
public:
    StateRpcService();

    // 启动rpc服务器
    void Start();

private:
    // srpc服务器对象
    grpc::ServerBuilder builder;

    StateServerRpcServiceImpl state_server_service_impl_;

    std::unique_ptr<grpc::Server> server_;
};