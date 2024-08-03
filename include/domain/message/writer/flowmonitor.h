#pragma once

#include <vector>
#include <mutex>
#include <string>

enum class ProtocolState 
{
    PUSH,       // 由服务器push超大群聊消息
    PULL        // 由服务器pull超大群聊消息
};

/// @brief 每个超大群聊session会对应一个这样的监视器对象
class FlowMonitor
{
public:
    FlowMonitor();
    FlowMonitor(uint64_t session_id);

    void SetSessionID(uint64_t session_id);
    uint64_t GetSessionID();

    void SetTimerId(uint32_t timer_id);
    uint32_t GetTimerId();

    /// @brief 放入消息到容器中
    /// @param msg 这个是序列化后的PushMsg，方便定时器直接批量发出去
    void PushMessage(uint64_t message_id, std::string& msg);

    /// @brief 是否需要协议降级
    /// @return 
    bool CheckProtocolDowngrade();
    /// @brief 协议降级的具体操作
    void ProtocolDowngrade();

    /// @brief 发送会话消息的定时任务，在创建完一个会话的监视器对象后就需要注册这么一个定时任务定时发送消息，
    /// 以及消息协议升级后得调用它注册定时任务
    void SetSendMessageTask();

private:
    /// @brief 打包消息并通知MessageSender发送消息，清空容器
    void SendContainerMessage();

    /// @brief 临时存放超大群聊消息的容器，key是messageID，value是序列化后的消息，要设置messageID的原因是消息最后要打包成PushMsg
    /// 可以直接拿messageID字段填充PushMsg
    std::vector<std::pair<uint64_t, std::string>> message_container_;

    /// @brief 该监视器的sessionID
    uint64_t session_id_;

    /// @brief 互斥锁，定时器打包清空容器消息时得确保线程安全
    std::mutex mtx_;

    /// @brief 超大群聊消息升降级的消息量阈值，当容器中的消息量超出该阈值时，认为该会话应当进行消息降级
    /// 这里偷个懒，当消息容量小于该阈值的0.75倍时就进行消息升级操作，数值随意定的，没有得到工程实践验证
    uint32_t threshold_;

    uint32_t timer_id_;

    /// @brief 当前容器的协议处于什么状态
    ProtocolState protocol_state_;
};