#pragma once

#include "conf.h"
#include <string>
#include <vector>

class CacheConfig
{
public:
    static CacheConfig& Get();

    std::vector<std::string> GetCacheRedisEndpointList();

private:
    CacheConfig() = default;

    CacheConfig(const CacheConfig&) = delete;
    CacheConfig& operator= (const CacheConfig&) = delete;
};