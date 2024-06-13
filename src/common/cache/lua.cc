#include "cache/lua.h"

LuaScript::LuaScript()
{
    // 这个脚本用来设置max_client_id比较并自增的，看文档《实现State Server（三）-分布式化（高可用&可伸缩性）》
    lua_script_table_.emplace(LuaScriptName::LuaCompareAndIncrClientID, std::make_pair("", 
        "if redis.call('exists', KEYS[1]) == 0 then redis.call('set', KEYS[1], 0) end;if redis.call('get', KEYS[1]) == ARGV[1] then redis.call('incr', KEYS[1]);redis.call('expire', KEYS[1], ARGV[2]); return 1 else return -1 end"));
}

std::pair<std::string, std::string> LuaScript::GetLuaScript(LuaScriptName key)
{
    auto res = lua_script_table_.find(key);
    if (res != lua_script_table_.end()) 
    {
        return res->second;
    }
    
    return std::make_pair("", "");
}

std::vector<LuaScriptName> LuaScript::GetKeys()
{
    std::vector<LuaScriptName> keys;
    keys.reserve(lua_script_table_.size());

    for (auto& lua_pair : lua_script_table_)
    {
        keys.emplace_back(lua_pair.first);
    }

    return keys;
}

void LuaScript::SetLuaScriptSha(LuaScriptName key, std::string& sha)
{
    auto res = lua_script_table_.find(key);
    if (res != lua_script_table_.end()) 
    {
        res->second.first = sha;
    }
}
