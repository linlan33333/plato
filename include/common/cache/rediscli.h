#pragma once

#include "lua.h"
#include <sw/redis++/redis++.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <spdlog/spdlog.h>

using namespace sw::redis;

class RedisCli
{
public:

    /// @brief 单例模式，因为很多模块都得使用，接入层、业务层等等
    /// @return 
    static RedisCli& Get();

    /// @brief 初始化redis集群
    void Init();

    /// @brief 获取UInt64数据
    /// @param key 
    /// @return 
    uint64_t GetUInt64(const std::string &key);

    /// @brief 设置字节数据，主要是用于存储protobuf序列化后的二进制数据
    /// @param key 
    /// @param value 
    /// @param ttl 
    void SetBytes(const std::string &key, const std::string &value, std::chrono::seconds ttl);

    /// @brief 获取字节数据，主要是获取存储在redis中的protobuf序列化后的二进制数据
    /// @param key 
    /// @return 返回string类型的字符串就行，它可以存储二进制数据
    std::string GetBytes(const std::string &key);

    /// @brief 删除键，批量删除
    /// @param keys 
    void Del(const std::vector<std::string> &keys);

    /// @brief 添加集合成员
    /// @param key 
    /// @param member 
    void SADD(const std::string &key, const std::string &member);

    /// @brief 删除集合成员
    /// @param key 
    /// @param members 
    void SREM(const std::string &key, const std::vector<std::string> &members);

    /// @brief 获取集合成员
    /// @param key 
    /// @return 
    std::unordered_set<std::string> SmembersStrSlice(const std::string &key);

    /// @brief 自增键
    /// @param key 
    /// @param ttl 
    void Incr(const std::string &key, std::chrono::seconds ttl);

    /// @brief 设置字符串
    /// @param key 
    /// @param value 
    /// @param ttl 
    void SetString(const std::string &key, const std::string &value, std::chrono::seconds ttl);

    /// @brief 获取字符串
    /// @param key 
    /// @return 
    std::string GetString(const std::string &key);

    /// @brief 运行 Lua 脚本，模板参数类型请填写key的类型、args的类型，注意只支持long long、void、bool、string这些类型
    /// @param name 
    /// @param keys 
    /// @param args 
    /// @return 
    template<typename Key_Type, typename Args_Type>
    int RunLuaInt(LuaScriptName name, std::vector<Key_Type> &keys, std::vector<Args_Type> &args)
    {
        std::pair<std::string, std::string> lua_pair = lua_scripts_.GetLuaScript(name);
        std::string sha = lua_pair.first;
        // 这个模板参数只支持long long、void、bool、string这些，其他的什么int都不支持，很傻逼
        long long res = rdb_->evalsha<long long>(sha, keys.begin(), keys.end(), args.begin(), args.end());

        return (int)res;
    }

    /// @brief 获取键列表，这里封装了一下，可以对整个redis集群中的所有实例拿到符合pattern的键
    /// @param pattern 
    /// @return 
    std::vector<std::string> GetKeys(std::string &pattern);

    /// @brief mget接口，获取传入的所有key对应的value
    /// @param keys 
    /// @return 
    std::vector<std::string> Mget(std::vector<std::string>& keys);

    /// @brief 集群环境中模拟mset命令批量插入数据，但是由于不同的key在不同的slot上，所以本质上还是一个一个地插入数据，后续看看怎么优化这个东西
    /// @param kv_pairs 
    /// @param ttl 
    void Mset(std::vector<std::pair<std::string, std::string>>& kv_pairs, std::chrono::seconds ttl);

    /// @brief 集群中的所有实例都存储一遍lua脚本，不然执行lua脚本切换到其他redis实例时没有存储该lua脚本
    /// 就无法拿sha去指示redis执行该脚本
    /// @param name 
    void InitLuaScript();

private:
    RedisCli() = default;

    RedisCli(const RedisCli&) = delete;
    RedisCli& operator= (const RedisCli&) = delete;

    // Redis连接对象，这是个集群的主服务器连接对象
    std::unique_ptr<RedisCluster> rdb_;

    // lua脚本容器的对象
    LuaScript lua_scripts_;
};

