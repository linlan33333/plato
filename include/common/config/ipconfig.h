#pragma once

#include "conf.h"
#include <string>

class IpConfConfig
{
public:
    static IpConfConfig& Get() {
        static IpConfConfig conf;
        return conf;
    }

    std::string GetServicePathForIPConf();

    // std::string GetCacheRedisEndpointList();

private:
    IpConfConfig() = default;

    IpConfConfig& operator= (const IpConfConfig&) = delete;
    IpConfConfig(const IpConfConfig&) = delete;

};