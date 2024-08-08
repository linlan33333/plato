#include "router/rpc/service/service.h"
#include "config/router.h"

RouterRpcService::RouterRpcService()
{
    std::string addr = RouterServerConfig::Get().GetIp() + ":" + std::to_string(RouterServerConfig::Get().GetPort());
    builder_.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder_.RegisterService(&router_server_serivce_impl_);
    server_ = builder_.BuildAndStart();
}

void RouterRpcService::Start()
{
    server_->Wait();
}