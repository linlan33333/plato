#include "config/ipconfig.h"
#include "config/conf.h"

std::string IpConfConfig::GetServicePathForIPConf()
{
    return Conf::GetConf()["ip_conf"]["service_path"].as<std::string>();
}

// std::string IpConfConfig::GetCacheRedisEndpointList()
// {
//     return Conf::GetConf()["cache"]["redis"]["endpoints"].as<std::string>();
// }
