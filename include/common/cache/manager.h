#pragma once

#include "rediscli.h"

/// @brief 为了隔离开存储层和领域层，这里封装缓存的接口，让领域层直接使用这里的接口，目前底层还是用的Redis，后面可以随意更换
class CacheManager
{
public:
    /// @brief 批量在缓存中存储数据
    /// @param kv_pairs 
    /// @param ttl 
    void Mset(std::vector<std::pair<std::string, std::string>>& kv_pairs, std::chrono::seconds ttl);

    /// @brief 批量获取缓存中key对应的数据
    /// @param keys 
    /// @returns 
    std::vector<std::string> Mget(std::vector<std::string>& keys);

    /// @brief 批量删除缓存中的key对应的数据
    /// @param keys 传入要删除的key的数组
    void Mdel(std::vector<std::string>& keys);
};