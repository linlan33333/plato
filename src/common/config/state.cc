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
