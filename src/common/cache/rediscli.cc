#include "cache/rediscli.h"
#include "config/cache.h"

RedisCli &RedisCli::Get()
{
    static RedisCli redis_cli;
    return redis_cli;
}

RedisCli::RedisCli() 
{
    // redis集群的某个主节点信息，就取第一个
    sw::redis::ConnectionOptions conn_ops;
    std::string endpoint = CacheConfig::Get().GetCacheRedisEndpointList()[0];
    auto pos = endpoint.find(':');
    std::string host = endpoint.substr(0, pos);
    std::string port = endpoint.substr(pos + 1, endpoint.size() - pos);
    conn_ops.host = host;
    conn_ops.port = std::stoi(port);

    // 设置连接池大小，让请求负载均衡，通过多个连接发送，减小请求延迟
    sw::redis::ConnectionPoolOptions conn_pool_ops;
    conn_pool_ops.size = 10;

    // 创建redis连接对象
    rdb_ = std::make_unique<RedisCluster>(conn_ops, conn_pool_ops);

    // 初始化lua脚本
    InitLuaScript();
}

std::vector<char> RedisCli::GetBytes(const std::string &key)
{
    auto val = rdb_->get(key);
    if (val) {
        return std::vector<char>(val->begin(), val->end());
    } else {
        spdlog::warn("Redis GetBytes: key not found");
    }

    return std::vector<char> ();
}

uint64_t RedisCli::GetUInt64(const std::string &key)
{
    auto val = rdb_->get(key);
    if (val) {
        return std::stoull(*val);
    } else {
        spdlog::warn("Redis GetUInt64: key not found");
    }

    return 0;
}

void RedisCli::SetBytes(const std::string &key, const std::vector<char> &value, std::chrono::seconds ttl)
{
    rdb_->set(key, std::string(value.begin(), value.end()), std::chrono::milliseconds(ttl));
}

void RedisCli::Del(const std::vector<std::string> &keys)
{
    rdb_->del(keys.begin(), keys.end());
}

void RedisCli::SADD(const std::string &key, const std::string &member)
{
    rdb_->sadd(key, member);
}

void RedisCli::SREM(const std::string &key, const std::vector<std::string> &members)
{
    rdb_->srem(key, members.begin(), members.end());
}

std::unordered_set<std::string> RedisCli::SmembersStrSlice(const std::string &key)
{
    std::unordered_set<std::string> res;
    rdb_->smembers(key, std::inserter(res, res.begin()));
    return res;
}

void RedisCli::Incr(const std::string &key, std::chrono::seconds ttl)
{
    rdb_->incr(key);
    rdb_->expire(key, ttl);
}

void RedisCli::SetString(const std::string &key, const std::string &value, std::chrono::seconds ttl)
{
    rdb_->set(key, value, std::chrono::milliseconds(ttl));
}

std::string RedisCli::GetString(const std::string &key)
{
    auto val = rdb_->get(key);
    if (val) {
        return *val;
    } else {
        throw std::runtime_error("Redis GetString: key not found");
    }
}

std::vector<std::string> RedisCli::GetKeys(std::string &pattern)
{
    std::vector<std::string> res;
    rdb_->for_each([&] (Redis& endpoint) {
        std::vector<std::string> current_res;
        endpoint.keys(pattern, std::back_inserter(current_res));
        res.insert(res.end(), current_res.begin(), current_res.end());
    });

    return res;
}

void RedisCli::InitLuaScript()
{
    // 初始化lua脚本
    std::vector<LuaScriptName> lua_script_keys = lua_scripts_.GetKeys();
    
    // 集群中的每一台主节点都存储一下lua脚本
    rdb_->for_each([&] (Redis& endpoint) {
        for (auto& key : lua_script_keys)
        {
            std::pair<std::string, std::string> script = lua_scripts_.GetLuaScript(key);
            std::string sha = endpoint.script_load(script.second);
            // 因为每个redis实例存储相同的lua脚本后得到的sha校验码是一样的，重复存储无所谓
            lua_scripts_.SetLuaScriptSha(key, sha);
        }
    });
}

