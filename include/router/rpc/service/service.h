#pragma once

#include "router/rpc/service/impl.h"
#include "grpc/router/router.grpc.pb.h"

class RouterRpcService {
public:
    RouterRpcService();

    /// @brief 启动rpc服务器
    void Start();

private:
    grpc::ServerBuilder builder_;

    RouterRpcServiceImpl router_server_serivce_impl_;

    std::unique_ptr<grpc::Server> server_;
};