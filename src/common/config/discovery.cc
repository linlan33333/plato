#include "config/discovery.h"

std::string DiscoveryConfig::GetIpPortForDiscovery()
{
    return Conf::GetConf()["discovery"]["endpoints"].as<std::string>();
}
