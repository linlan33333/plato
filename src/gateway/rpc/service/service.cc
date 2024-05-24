#include "gateway/rpc/service/service.h"
#include "config/gateway.h"

GatewayRpcService::GatewayRpcService(NetService* net_service)
    : gateway_service_impl_(net_service)
{
    std::string addr = GatewayConfig::Get().GetIp() + ":" + std::to_string(GatewayConfig::Get().GetPortForRPCService());
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&gateway_service_impl_);
    server_ = builder.BuildAndStart();
}

void GatewayRpcService::Start()
{
    server_->Wait();
}