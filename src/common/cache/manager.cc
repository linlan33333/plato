#include "common/cache/manager.h"
#include "manager.h"

void CacheManager::Mset(std::vector<std::pair<std::string, std::string>> &kv_pairs, std::chrono::seconds ttl)
{
    RedisCli::Get().Mset(kv_pairs, ttl);
}

std::vector<std::string> CacheManager::Mget(std::vector<std::string> &keys)
{
    return RedisCli::Get().Mget(keys);
}

void CacheManager::Mdel(std::vector<std::string> &keys)
{
    RedisCli::Get().Del(keys);
}
