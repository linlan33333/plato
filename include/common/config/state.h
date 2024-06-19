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

    /// @brief state server处理消化RPC请求生成的任务的线程池线程数量，就是消化那个channel的消费者
    /// @return 
    uint32_t GetThreadNumForWorkPool();

    /// @brief 获取该state server存储connid的set集合名称的范围，这里将set集合视为逻辑上的登录槽
    // 因此它叫获取登录槽范围
    /// @return 
    std::pair<int, int> GetStateServerLoginSlotRange();

private:
    StateServerConfig() = default;

    StateServerConfig& operator= (const StateServerConfig&) = delete;
    StateServerConfig(const StateServerConfig&) = delete;
};