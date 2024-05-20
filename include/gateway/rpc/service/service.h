#pragma once

#include "srpc/gateway/gateway.srpc.h"

class GatewayRpcService
{
public:
    GatewayRpcService() = default;

    // 初始化rpc服务器，调用后就会运行，底层由srpc提供
    void Init();
};