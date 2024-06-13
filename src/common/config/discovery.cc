#include "config/discovery.h"

DiscoveryConfig &DiscoveryConfig::Get()
{
    static DiscoveryConfig conf;
    return conf;
}

std::string DiscoveryConfig::GetIpPortForDiscovery()
{
    return Conf::GetConf()["discovery"]["endpoints"].as<std::string>();
}
