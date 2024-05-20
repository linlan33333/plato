#pragma once

#include "conf.h"
#include <string>

class StateServerConfig
{
public:
    static StateServerConfig& Get();

    std::string GetIp();

    uint32_t GetPort();

private:
    StateServerConfig() = default;

    StateServerConfig& operator= (const StateServerConfig&) = delete;
    StateServerConfig(const StateServerConfig&) = delete;
};