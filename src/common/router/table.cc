#include "router/table.h"

Router::Router()
    : ttl7D_(7 * 24 * 60 * 60)
{

}

Router &Router::Get()
{
    static Router router;
    return router;
}

void Router::AddRecord(uint64_t did, std::string &endpoint, uint64_t connid)
{
    char key[100];
    sprintf(key, gateway_router_key_.c_str(), did);
    std::string value = endpoint + "-" + std::to_string(connid);

    std::cout << "该用户的登录信息key: " << key << std::endl; 

    RedisCli::Get().SetString(key, value, ttl7D_);
}

void Router::DelRecord(uint64_t did)
{
    char key[100];
    sprintf(key, gateway_router_key_.c_str(), did);
    std::vector<std::string> keys({key});

    RedisCli::Get().Del(keys);
}

Record Router::QueryRecord(uint64_t did)
{
    char key[100];
    sprintf(key, gateway_router_key_.c_str(), did);

    // 查询该用户的登录信息
    std::string endpoint_connid = RedisCli::Get().GetString(key);
    // 切割endpoint和connid并返回
    Record record;
    int pos = endpoint_connid.find('-');
    record.Endpoint = endpoint_connid.substr(0, pos);
    record.ConnID = std::stoull(endpoint_connid.substr(pos + 1, endpoint_connid.size()));

    return record;
}