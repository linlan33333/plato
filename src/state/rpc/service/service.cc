#include "state/rpc/service/service.h"
#include "config/state.h"

StateRpcService::StateRpcService()
{
    std::string addr = StateServerConfig::Get().GetIp() + ":" + std::to_string(StateServerConfig::Get().GetPort());
    builder_.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder_.RegisterService(&state_server_service_impl_);
    server_ = builder_.BuildAndStart();
}

void StateRpcService::Start()
{
    server_->Wait();
}
