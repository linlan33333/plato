#include "state/rpc/service/service.h"
#include "config/state.h"

StateRpcService::StateRpcService()
{
    server_.add_service(&state_server_service_impl_);
}

void StateRpcService::Start()
{
    server_.start(StateServerConfig::Get().GetPort());
}

void StateRpcService::Stop()
{
    server_.stop();
}