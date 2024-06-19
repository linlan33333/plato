#include "config/state.h"
#include "config/conf.h"
#include "state.h"

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

std::pair<int, int> StateServerConfig::GetStateServerLoginSlotRange()
{
    std::string range = Conf::GetConf()["state"]["conn_state_slot_range"].as<std::string>();
    int pos = range.find(',');
    std::string begin = range.substr(0, pos);
    std::string end = range.substr(pos + 1, range.size());
    return std::pair<int, int> (std::stoi(begin), std::stoi(end));
}