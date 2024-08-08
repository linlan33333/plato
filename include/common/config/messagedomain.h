#pragma once

#include "conf.h"
#include <string>
#include <vector>

class MessageDomainConfig
{
public:
    static MessageDomainConfig& Get();

    /// @brief 获取服务名称
    /// @return 
    std::string GetServiceName();

    /// @brief 获取服务的IP地址
    /// @return 
    std::string GetServiceAddr();

    /// @brief 获取服务的端口号
    /// @return 
    uint32_t GetServicePort();

    /// @brief 获取MySQL数据库的host信息
    /// @return 
    std::string GetMySQLHost();
    /// @brief 获取MySQL数据库的用户名
    /// @return 
    std::string GetMySQLUser();
    /// @brief 获取MySQL数据库的密码
    /// @return 
    std::string GetMySQLPassword();
    /// @brief 获取MySQL数据库的具体数据库名
    /// @return 
    std::string GetMySQLDataBase();

    /// @brief 获取TiDB数据库的IP地址
    /// @return 
    std::string GetTiDBAddr();
    /// @brief 获取TiDB数据库的端口号
    /// @return 
    uint32_t GetTiDBPort();
    /// @brief 获取TiDB数据库的用户名
    /// @return 
    std::string GetTiDBUser();
    /// @brief 获取TiDB数据库的具体数据库名
    /// @return 
    std::string GetTiDBDataBase();

    /// @brief 获取writer server的协议降级阈值
    /// @return 
    uint32_t GetProtocolDowngradeThreshold();

    /// @brief 获取超大群聊的消息推送频率
    uint32_t GetSuperSessionPushInterval();
};