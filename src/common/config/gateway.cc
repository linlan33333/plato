#include "config/gateway.h"
#include "config/conf.h"

GatewayConfig &GatewayConfig::Get()
{
    static GatewayConfig config;
    return config;
}

std::string GatewayConfig::GetIp()
{
    return Conf::GetConf()["gateway"]["service_addr"].as<std::string>();
}

uint32_t GatewayConfig::GetPortForNetService()
{
    return Conf::GetConf()["gateway"]["tcp_server_port"].as<std::uint32_t>();
}

uint32_t GatewayConfig::GetPortForRPCService()
{
    return Conf::GetConf()["gateway"]["rpc_server_port"].as<std::uint32_t>();
}

std::string GatewayConfig::GetServiceName()
{
    return Conf::GetConf()["gateway"]["service_name"].as<std::string>();
}

uint32_t GatewayConfig::GetThreadNumForRPCServer()
{
    return Conf::GetConf()["gateway"]["rpc_thread_num"].as<std::uint32_t>();
}

uint32_t GatewayConfig::GetThreadNumForNetServer()
{
    return Conf::GetConf()["gateway"]["tcp_thread_num"].as<std::uint32_t>();
}
