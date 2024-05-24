#pragma once

#include "gateway/netservice.h"
#include "gateway/rpc/service/impl.h"

class GatewayRpcService
{
public:
    GatewayRpcService(NetService* net_service);

    // 启动rpc服务器
    void Start();

private:
    grpc::ServerBuilder builder;

    GatewayRpcServiceImpl gateway_service_impl_;

    std::unique_ptr<grpc::Server> server_;
};