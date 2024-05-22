#pragma once

#include "srpc/state/state.srpc.h"
#include "state/rpc/service/impl.h"

class StateRpcService
{
public:
    StateRpcService();

    // 启动rpc服务器
    void Start();

    void Stop();

private:
    // srpc服务器对象
    srpc::SRPCServer server_;

    StateServerRpcServiceImpl state_server_service_impl_;
};