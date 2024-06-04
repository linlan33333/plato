#pragma once

#include <mutex>

// 该类表示用户的状态，以及状态改变的接口
class ConnectionState
{
public:
    ConnectionState() = default;
    ConnectionState(uint64_t connid, uint32_t did);

    void SetConnId(uint64_t connid);
    uint64_t GetConnId();

    void SetDeviceId(uint64_t did);
    uint64_t GetDeviceId();

    void SetHeartTimerId(uint32_t timerid);
    uint32_t GetHeartTimerId();

    /// @brief 重设心跳计时器
    void ResetHeartBeatTimer();
    /// @brief 删除心跳计时器
    void DeleteHeartBeatTimer();

    void SetReConnTimerId(uint32_t timerid);
    uint32_t GetReConnTimerId();

    /// @brief 重设重连定时器
    void SetReConnTimer();
    /// @brief 删除重连计时器
    void DeleteReConnTimer();

    void SetMsgTimerId(uint32_t timerid);
    uint32_t GetMsgTimerId();

    /// @brief 销毁该连接状态，停掉所有定时器，处理后事
    void Close();

private:
    // 同一个用户的状态的变更得是串行的，想调用接口改变状态，先抢这把锁
    std::mutex mtx_;

    // 用户在网关中的连接对象的key
    uint64_t connid_;

    // 类似于用户的qq号，是用户的唯一标识
    uint64_t did_;

    // 心跳定时器的id，等于0标识没有设置该定时器，记得删除定时器的时候把它改为0
    uint32_t heart_timer_id_ = 0;

    // 重连计时器的id，等于0标识没有设置该定时器，记得删除定时器的时候把它改为0
    uint32_t reconn_timer_id_ = 0;

    // 发送上行消息后的定时器id，等于0标识没有设置该定时器，记得删除定时器的时候把它改为0
    uint32_t msg_timer_id_ = 0;
};