#pragma once

#include "conf.h"
#include <string>

class DiscoveryConfig
{
public:
    static DiscoveryConfig& Get()
    {
        static DiscoveryConfig conf;
        return conf;
    }

    /// @brief 从配置文件对象中获取服务发现服务器的ip地址端口号
    /// @return 看服务发现中间件设置ip地址端口号的格式，zookeeper是“ip:port”形式
    std::string GetIpPortForDiscovery();

private:
    DiscoveryConfig() = default;

    DiscoveryConfig(const DiscoveryConfig& conf) = delete;
    DiscoveryConfig& operator= (const DiscoveryConfig& conf) = delete;
};