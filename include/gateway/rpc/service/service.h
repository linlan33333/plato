#pragma once

#include "srpc/gateway/gateway.srpc.h"
#include "gateway/netservice.h"
#include "gateway/rpc/service/impl.h"

class GatewayRpcService
{
public:
    GatewayRpcService(NetService* net_service);

    // 启动rpc服务器
    void Start();

    void Stop();

private:
    // srpc服务器对象
    srpc::SRPCServer server_;

    GatewayRpcServiceImpl gateway_service_impl_;
};