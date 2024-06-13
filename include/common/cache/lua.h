#pragma once

#include <string>
#include <map>
#include <vector>

// 所有lua脚本的名字放到这里
enum class LuaScriptName
{
    LuaCompareAndIncrClientID
};

// 把所有lua脚本都集中到这个类中
class LuaScript
{
public:
    // 有什么lua脚本提前设置好的可以在这里面手动添加
    LuaScript();

    std::pair<std::string, std::string> GetLuaScript(LuaScriptName key);

    std::vector<LuaScriptName> GetKeys();

    void SetLuaScriptSha(LuaScriptName key, std::string& sha);

private:
    // 存储lua脚本的map表，key是脚本名称，value是个pair，其中key是sha（lua脚本缓存到redis中后，
    // redis返回的sha1校验码，以后可以拿着这个校验码让redis执行对应的脚本），value是脚本内容

    // 这里有一个坑点：当你给一台redis集群的主节点存储lua脚本时，会得到一个sha校验码，如果你
    // 使用sha校验码让该主节点执行lua脚本，但是lua脚本中需要存取数据，这个数据的key是携带计算插槽值的{XXX}的，
    // 那么当计算出来的插槽slot不在这台redis实例时，会切换连接到slot所在的redis实例，这就造成一个问题：
    // 以后你再使用sha校验码发给redis实例让它执行lua脚本时，你发过去的redis实例是切换后的实例，但它没有存储该lua脚本，
    // 因此不认识sha校验码！就会报错该实例找不到lua脚本。

    // 解决方法放到rediscli.h中去做：不同的redis实例存储lua脚本时得到的sha校验码是一样的，因为都是
    // 同一个摘要算法算出来的，因此让没存过的redis实例存储一下lua脚本不就行了？所以初始化Redis连接对象时就
    // 找到所有redis实例都存储一遍
    std::map<LuaScriptName, std::pair<std::string, std::string>> lua_script_table_;
};