#pragma once

#include "conf.h"
#include <string>

class StateServerConfig
{
public:
    static StateServerConfig& Get();

    std::string GetIp();

    /// @brief 其实state server只会启动一个rpc服务器，这个端口号是这个rpc服务器的
    /// @return 
    uint32_t GetPort();

private:
    StateServerConfig() = default;

    StateServerConfig& operator= (const StateServerConfig&) = delete;
    StateServerConfig(const StateServerConfig&) = delete;
};