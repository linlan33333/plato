#include "common/config/router.h"

RouterServerConfig &RouterServerConfig::Get()
{
    static RouterServerConfig instance;
    return instance;
}

std::string RouterServerConfig::GetIp()
{
    return Conf::GetConf()["router"]["service_addr"].as<std::string>();
}

uint32_t RouterServerConfig::GetPort()
{
    return Conf::GetConf()["router"]["service_port"].as<uint32_t>();
}

uint32_t RouterServerConfig::GetThreadNumForWorkPool()
{
    return Conf::GetConf()["router"]["workpool_thread_num"].as<uint32_t>();
}