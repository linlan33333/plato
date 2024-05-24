#include "state/rpc/service/service.h"
#include "config/state.h"

StateRpcService::StateRpcService()
{
    std::string addr = StateServerConfig::Get().GetIp() + ":" + std::to_string(StateServerConfig::Get().GetPort());
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&state_server_service_impl_);
    server_ = builder.BuildAndStart();
}

void StateRpcService::Start()
{
    server_->Wait();
}
