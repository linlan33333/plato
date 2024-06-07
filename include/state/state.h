#pragma once

#include <mutex>
#include <atomic>

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


    void SetMaxClientId(uint64_t client_id);
    uint64_t GetMaxClientId();
    /// @brief 让max_client_id自增
    void AddMaxClientId();


    void SetMsgId(uint64_t msg_id);
    uint64_t GetMsgId();
    /// @brief 让msg_id自增
    void AddMsgId();


    void SetHeartTimerId(uint32_t timerid);
    uint32_t GetHeartTimerId();
    /// @brief 重设心跳计时器
    void ResetHeartBeatTimer();
    /// @brief 删除心跳计时器
    void DeleteHeartBeatTimer();


    void SetReConnTimerId(uint32_t timerid);
    uint32_t GetReConnTimerId();
    /// @brief 重设重连定时器
    void ResetReConnTimer();
    /// @brief 删除重连计时器
    void DeleteReConnTimer();


    void SetMsgTimerId(uint32_t timerid);
    uint32_t GetMsgTimerId();
    void DeleteMsgTimer();


    /// @brief 销毁该连接状态，停掉所有定时器，处理后事
    void Close();

    /// @brief 检查客户端发来的消息的id是否连贯，也就是确保上行消息可靠性
    /// @param client_id 
    /// @return 
    bool CheckUPMsg(uint64_t client_id);

    

private:
    // 同一个用户的状态的变更得是串行的，想调用接口改变状态，先抢这把锁
    std::mutex mtx_;

    // 用户在网关中的连接对象的key
    uint64_t connid_;

    // 类似于用户的qq号，是用户的唯一标识
    uint64_t did_;

    // 该客户端发送消息的最大消息id，依靠这个确保上行消息可靠性，不管用户发送单聊群聊，都需要客户端自己递增
    // 然后发过来，在这里存储起来，然后比较，当把这个消息转发给业务服务器，并收到确认时，才增加该id
    uint64_t max_client_id_ = 0;

    // 给该客户端发送消息的最新消息id，测试用，这玩意得由分布式id生成服务去做
    uint64_t msg_id_ = 0;

    // 心跳定时器的id，等于0标识没有设置该定时器，记得删除定时器的时候把它改为0
    uint32_t heart_timer_id_ = 0;

    // 重连计时器的id，等于0标识没有设置该定时器，记得删除定时器的时候把它改为0
    uint32_t reconn_timer_id_ = 0;

    // 发送上行消息后的定时器id，等于0标识没有设置该定时器，记得删除定时器的时候把它改为0
    uint32_t msg_timer_id_ = 0;
};