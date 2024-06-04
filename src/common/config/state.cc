#include "config/state.h"
#include "config/conf.h"

StateServerConfig &StateServerConfig::Get()
{
    static StateServerConfig conf;
    return conf;
}

std::string StateServerConfig::GetIp()
{
    return Conf::GetConf()["state"]["service_addr"].as<std::string>();
}

uint32_t StateServerConfig::GetPort()
{
    return Conf::GetConf()["state"]["server_port"].as<std::uint32_t>();
}

uint32_t StateServerConfig::GetThreadNumForWorkPool()
{
    return Conf::GetConf()["state"]["workpool_thread_num"].as<std::uint32_t>();
}