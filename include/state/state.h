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


    void SetMsgId(uint64_t msgid);
    uint64_t GetMsgId();
    /// @brief 让msg_id自增
    void AddMsgId();


    void SetHeartTimerId(uint32_t timerid);
    uint32_t GetHeartTimerId();
    /// @brief 重设心跳计时器，如果没有就创建心跳定时器
    void ResetHeartBeatTimer();
    /// @brief 删除心跳计时器
    void DeleteHeartBeatTimer();


    void SetReConnTimerId(uint32_t timerid);
    uint32_t GetReConnTimerId();
    /// @brief 重设重连定时器
    void ResetReConnTimer();
    /// @brief 删除重连计时器
    void DeleteReConnTimer();


    uint32_t GetMsgTimerId();
    /// @brief 重设消息定时器，同时还需要存储一些元数据才行
    void ResetMsgTimer(uint64_t sessionid, uint64_t msgid);
    /// @brief 删除消息定时器，得先验证传入的元信息锁
    /// @param msg_timer_lock 
    void DeleteMsgTimer(std::string& msg_timer_lock);


    /// @brief 该接口不应当单独使用，设置msg_timer_lock_和创建定时器应当是原子操作，不应该分开调用
    /// @param sessionid 
    /// @param msgid 
    void SetMsgTimerLock(uint64_t sessionid, uint64_t msgid);
    std::string GetMsgTimerLock();

    /// @brief 设置push_msg元信息锁msg_timer_lock_，创建重发定时器，将push_msg_str存储到redis飞行队列中，这三步操作是原子性操作
    /// @param last_msg_key 
    /// @param sessionid 
    /// @param msgid 
    /// @param push_msg_str 
    void AppendMsg(std::string last_msg_key, uint64_t sessionid, uint64_t msgid, std::string& push_msg_str);
    /// @brief 检查当前ACK消息是不是最新消息的ACK消息，是的话就删除定时器，删除飞行队列中的消息，这两步是原子操作
    /// @param sessionid 
    /// @param msgid 
    void AckLastMsg(uint64_t sessionid, uint64_t msgid);

    /// @brief 销毁该连接状态，停掉所有定时器，处理后事
    void Close();

private:
    // 同一个用户的状态的变更得是串行的，想调用接口改变状态，先抢这把锁
    std::mutex mtx_;

    // 用户在网关中的连接对象的key
    uint64_t connid_;

    // uid是用户的唯一标识，类似于qq号，该用户可能有多台设备同时登录，那么这些设备的id就是did
    // 如果支持多端登录，那么业务方还需要维护一个uid到did的映射表
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

    // 发送上行消息后的定时器id，只有最新的消息有定时器，等于0标识没有设置该定时器，记得删除定时器的时候把它改为0
    uint32_t msg_timer_id_ = 0;

    // 最新的消息的元信息锁，防止老旧消息的ACK消息把最新消息的定时器给销毁了
    std::string msg_timer_lock_;
};