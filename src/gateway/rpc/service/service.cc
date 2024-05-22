#include "gateway/rpc/service/service.h"
#include "gateway/rpc/service/impl.h"
#include "config/gateway.h"

GatewayRpcService::GatewayRpcService(NetService *net_service)
    : gateway_service_impl_(net_service)
{
    // 注册服务
    server_.add_service(&gateway_service_impl_);
}

void GatewayRpcService::Start()
{
    // 启动rpcserver
    server_.start(GatewayConfig::Get().GetPortForRPCService());
}

void GatewayRpcService::Stop()
{
    server_.stop();
}