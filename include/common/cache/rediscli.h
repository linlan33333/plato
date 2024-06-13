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

    /// @brief 获取字节数据
    /// @param key 
    /// @return 
    std::vector<char> GetBytes(const std::string &key);

    /// @brief 获取UInt64数据
    /// @param key 
    /// @return 
    uint64_t GetUInt64(const std::string &key);

    /// @brief 设置字节数据
    /// @param key 
    /// @param value 
    /// @param ttl 
    void SetBytes(const std::string &key, const std::vector<char> &value, std::chrono::seconds ttl);

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

    /// @brief 运行 Lua 脚本，模板参数类型请填写key的类型、args的类型
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

    /// @brief 集群中的所有实例都存储一遍lua脚本，不然执行lua脚本切换到其他redis实例时没有存储该lua脚本
    /// 就无法拿sha去指示redis执行该脚本
    /// @param name 
    void InitLuaScript();

private:
    RedisCli();

    RedisCli(const RedisCli&) = delete;
    RedisCli& operator= (const RedisCli&) = delete;

    // Redis连接对象，这是个集群的主服务器连接对象
    std::unique_ptr<RedisCluster> rdb_;

    // lua脚本容器的对象
    LuaScript lua_scripts_;
};

// // redis cache 类
// class redisCache {
// public:
//     redisCache() = default;

//     void MSet(const std::map<std::string, std::string> &keys) {
//         rdb->mset(keys.begin(), keys.end());
//     }

//     std::map<std::string, std::string> MGet(const std::vector<std::string> &keys) {
//         auto result = rdb->mget(keys.begin(), keys.end());
//         std::map<std::string, std::string> resultMap;
//         for (size_t i = 0; i < keys.size(); ++i) {
//             if (result[i]) {
//                 resultMap[keys[i]] = *result[i];
//             }
//         }
//         return resultMap;
//     }

//     void MDel(const std::vector<std::string> &keys) {
//         rdb->del(keys.begin(), keys.end());
//     }
// };

// int main() {
//     try {
//         InitRedis();

//         // 测试函数
//         SetString("test_key", "test_value", std::chrono::seconds(60));
//         std::cout << "Value of test_key: " << GetString("test_key") << std::endl;

//     } catch (const Error &e) {
//         std::cerr << "Redis error: " << e.what() << std::endl;
//     }

//     return 0;
// }
