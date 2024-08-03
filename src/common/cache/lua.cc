#include "cache/lua.h"

LuaScript::LuaScript()
{
    // 这个脚本用来设置max_client_id比较并自增的，看文档《实现State Server（三）-分布式化（高可用&可伸缩性）》
    lua_script_table_.emplace(LuaScriptName::LuaCompareAndIncrClientID, std::make_pair("", 
        "if redis.call('exists', KEYS[1]) == 0 then redis.call('set', KEYS[1], 0) end;if redis.call('get', KEYS[1]) == ARGV[1] then redis.call('incr', KEYS[1]);redis.call('expire', KEYS[1], ARGV[2]); return 1 else return -1 end"));
    
    // 这个lua脚本的思想就是在redis的插槽中存储同一个会话中的下一条messageID，当客户端请求该会话中的下一条messageID时，redis能返回该messageID并让messageID加一，
    // 以应对下一次请求。同时redis在返回messageID时会判断当前redis实例的runID是否是上一次分配messageID时的runID，如果不是，那么messageID会增加10000。
    // 这么做的原因在于每个会话中的messageID需要单调递增，所以使用redis的lua脚本生成messageID，参考文档《消息协议设计(二)-消息可用性》
    lua_script_table_.emplace(LuaScriptName::LuaGetSessionMessageID, std::make_pair("", 
     R"(local session_id = KEYS[1] 
        local current_server_id = redis.call('info', 'run_id')
        if redis.call('EXISTS', session_id) == 0 then
            redis.call('SET', session_id, '1:' .. current_server_id)
            return 0
        end
        local msg_server_id = redis.call('GET', session_id)
        local t = {}
        for str in string.gmatch(msg_server_id, '([^:]+)') do
            table.insert(t, str)
        end
        local msg_id = tonumber(t[1])
        local last_server_id = t[2]
        if last_server_id ~= current_server_id then
            msg_id = msg_id + 10000
        end
        local next_msg_id = msg_id + 1
        redis.call('SET', session_id, next_msg_id .. ":" .. current_server_id)
        return msg_id
    )"));
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
