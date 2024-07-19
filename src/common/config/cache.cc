#include "config/cache.h"

CacheConfig &CacheConfig::Get()
{
    static CacheConfig cache;
    return cache;
}

std::vector<std::string> CacheConfig::GetCacheRedisEndpointList()
{
    std::vector<std::string> res;
    auto nodes = Conf::GetConf()["cache"]["redis"]["endpoints"];
    for (auto endpoint : nodes)
    {
        res.emplace_back(endpoint.as<std::string>());
    }

    return res;
}