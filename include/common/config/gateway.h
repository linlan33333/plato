#pragma once

#include "conf.h"
#include <string>

class GatewayConfig
{
public:
    static GatewayConfig& Get();

    std::string GetIp();

    uint32_t GetPortForNetService();

    uint32_t GetPortForRPCService();

    std::string GetServiceName();

    uint32_t GetThreadNumForRPCServer();

    uint32_t GetThreadNumForNetServer();

private:
    
    GatewayConfig() = default;

    GatewayConfig& operator= (const GatewayConfig& conf) = delete;
    GatewayConfig(const GatewayConfig& conf) = delete;
};