#pragma once

#include "flowmonitor.h"
#include <vector>
#include <string>
#include <map>
#include <memory>

class FlowController
{
public:
    static FlowController& Get();

    /// @brief 将会话的聊天消息放入对应的监控器容器中，同时检查该会话的消息是否超出阈值了，超出就调用协议升级的接口
    /// 表示需要进行协议降级
    /// @param session_id 
    /// @param msg 
    /// @return true表示需要进行协议降级
    void AddMessageAndCheckFlow(uint64_t session_id, uint64_t message_id, std::string& msg);

private:
    FlowController() = default;
    FlowController(const FlowController&) = delete;
    FlowController& operator=(const FlowController&) = delete;

    /// @brief 超大群聊会话的流量监控表，key是sessionID
    std::map<uint64_t, std::shared_ptr<FlowMonitor>> session_flow_monitors_;

    // 流量监控表的互斥锁，写的时候需要加锁，读不需要
    std::mutex mtx_;
};