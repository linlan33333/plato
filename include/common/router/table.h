#pragma once

#include "cache/rediscli.h"
#include <string>
#include <chrono>

/// @brief 记录某个用户did对应的连接在哪个state server（通过Endpoint指定），连接id是啥（通过ConnID指定）
struct Record
{
    std::string Endpoint;
    uint64_t ConnID;
};

/// @brief 提供给IM server业务层操作的路由接口类，通过该类的成员方法可以查找某个用户did的连接在哪台state server上，
/// 从而把消息推送过去，最终交付给用户
class Router
{
public:
    static Router& Get();

    /// @brief 当用户登录时调用，向redis中添加该用户的登录信息，即该用户的连接在哪台state server中，connid是多少
    /// @param did
    /// @param endpoint 
    /// @param connid 
    void AddRecord(uint64_t did, std::string& endpoint, uint64_t connid);

    /// @brief 当用户登出时调用，删掉redis中该用户的登录信息
    /// @param did 
    void DelRecord(uint64_t did);

    /// @brief IM server专用，查询该did对应的用户所在的state server ip地址信息和connid信息，方便后续推送消息
    /// @param did 
    /// @return 
    Record QueryRecord(uint64_t did);

private:
    Router();

    Router(const Router&) = delete;
    Router& operator= (const Router&) = delete;

    /// @brief 这个变量只会在本类中用到，干脆封装成成员变量吧
    std::string gateway_router_key_ = "gateway_router_%llu";
    /// @brief 过期时间7天
    std::chrono::seconds ttl7D_;
};