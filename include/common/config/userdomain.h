#pragma once

#include "conf.h"
#include <string>
#include <vector>

class UserDomainConfig
{
public:
    static UserDomainConfig& Get();

    /// @brief 获取服务名称
    /// @return 
    std::string GetServiceName();

    /// @brief 获取服务的IP地址
    /// @return 
    std::string GetServiceAddr();

    /// @brief 获取服务的端口号
    /// @return 
    uint32_t GetServicePort();

    /// @brief 获取数据库的host信息
    /// @return 
    std::string GetDBHost();
    /// @brief 获取数据库的用户名
    /// @return 
    std::string GetUser();
    /// @brief 获取数据库的密码
    /// @return 
    std::string GetPassword();
    /// @brief 获取数据库的具体数据库名
    /// @return 
    std::string GetDataBase();

    /// @brief redis回源场景可以将数据存放到缓存的操作异步交给线程池处理
    /// @return 
    uint32_t GetThreadNumForWorkPool();

private:
    UserDomainConfig() = default;
    UserDomainConfig(const UserDomainConfig&) = delete;
    UserDomainConfig& operator=(const UserDomainConfig&) = delete;
};