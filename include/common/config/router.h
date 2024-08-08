#pragma once

#include "conf.h"
#include <string>

class RouterServerConfig {
public:
    static RouterServerConfig& Get();

    std::string GetIp();

    uint32_t GetPort();

    /// @brief router server调用state server的RPC接口推送消息应该是并行的，所以这里使用了线程池
    /// @return 
    uint32_t GetThreadNumForWorkPool();

private:
    RouterServerConfig() = default;

    RouterServerConfig(const RouterServerConfig&) = delete;
    RouterServerConfig& operator=(const RouterServerConfig&) = delete;
};