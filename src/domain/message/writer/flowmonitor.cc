#include "domain/message/writer/flowmonitor.h"
#include "common/config/messagedomain.h"
#include "flowmonitor.h"
#include "messagesender.h"
#include "common/idl/message/message.pb.h"
#include "common/idl/domain/message/message_dto.pb.h"
#include "timer.h"
#include <spdlog/spdlog.h>

FlowMonitor::FlowMonitor()
    : threshold_(MessageDomainConfig::Get().GetProtocolDowngradeThreshold())
    , timer_id_(0)
    , protocol_state_(ProtocolState::PUSH)
{
}

FlowMonitor::FlowMonitor(uint64_t session_id)
    : threshold_(MessageDomainConfig::Get().GetProtocolDowngradeThreshold())
    , session_id_(session_id)
    , timer_id_(0)
    , protocol_state_(ProtocolState::PUSH)
{
}

void FlowMonitor::SetSessionID(uint64_t session_id)
{
    session_id_ = session_id;
}

uint64_t FlowMonitor::GetSessionID()
{
    return session_id_;
}

void FlowMonitor::SetTimerId(uint32_t timer_id)
{
    timer_id_ = timer_id;
}

uint32_t FlowMonitor::GetTimerId()
{
    return timer_id_;
}

void FlowMonitor::PushMessage(uint64_t message_id, std::string& msg)
{
    // 操作该容器可能涉及到并发安全，比如定时器在清空容器发送数据，另一个线程再往里面放数据
    std::lock_guard<std::mutex> lock(mtx_);

    message_container_.emplace_back(std::make_pair(message_id, msg));
}

bool FlowMonitor::CheckProtocolDowngrade()
{
    // 这个对一致性要求不高就不上锁了
    return message_container_.size() >= threshold_;
}

void FlowMonitor::ProtocolDowngrade()
{
    std::lock_guard<std::mutex> lock(mtx_);

    // 已经是协议降级状态就没必要重复降级
    if (protocol_state_ == ProtocolState::PULL)
    {
        return;
    }

    // 设置消息协议为拉模式
    protocol_state_ = ProtocolState::PULL;

    // 调用MessageSender发送协议回退的特殊消息
    // 这里需要先组装一个协议回退的消息，然后发出去
    message::MessageDTO message_dto;
    message_dto.set_commandtype(message::CommandType::PROTOCOLDOWNGRADE);
    std::string message_str;
    if (!message_dto.SerializeToString(&message_str)) 
    {
        spdlog::warn("FlowMonitor.cc::ProtocolDowngrade: MessageDTO serialize to string error!");
        return;
    }
    MessageSender::Get().FanoutMessage(message::PushBatch, message_str);
}

void FlowMonitor::SetSendMessageTask()
{
    // 上锁，防止定时任务被多个线程设置多次，而且最多只能存在一个定时任务，这一点已经由FlowController的双重检查实现了
    std::lock_guard<std::mutex> lock(mtx_);

    if (protocol_state_ == ProtocolState::PUSH)
    {
        SendContainerMessage();
    }
    else if (protocol_state_ == ProtocolState::PULL)
    {
        // 如果满足协议升级的需求
        if (message_container_.size() <= 0.75 * threshold_)
        {
            protocol_state_ == ProtocolState::PUSH;

            // 调用MessageSender发送协议升级的特殊消息
            message::MessageDTO message_dto;
            message_dto.set_commandtype(message::CommandType::PROTOCOLUPGRADE);
            std::string message_str;
            if (!message_dto.SerializeToString(&message_str)) 
            {
                spdlog::warn("FlowMonitor.cc::SetSendMessageTask: MessageDTO serialize to string error!");
                return;
            }
            MessageSender::Get().FanoutMessage(message::PushBatch, message_str);

            // 需要立即发送这批消息数据
            SendContainerMessage();
        }
        else 
        {
            // 不满足的话就清空容器，不需要发送这批消息
            message_container_.clear();
        }
    }
    // 后续有新的协议状态就自行拓展

    // 重置定时器，递归调用本函数
    timer_id_ = Timer::Get().RunAfter(MessageDomainConfig::Get().GetSuperSessionPushInterval(), std::bind(FlowMonitor::SetSendMessageTask, this));
}

void FlowMonitor::SendContainerMessage()
{
    if (message_container_.size() == 0) 
    {
        return;
    }

    // 构造接入层接收的MsgCmd
    message::PushMultiMsg messages;
    messages.set_sessionid(session_id_);
    auto content = messages.mutable_content();

    for (auto& message_pair : message_container_)
    {
        content->insert({message_pair.first, message_pair.second});
    }

    // 这批消息打包好了就全部清除掉
    message_container_.clear();

    std::string session_msg_str;
    if (!messages.SerializeToString(&session_msg_str))
    {
        spdlog::warn("FlowMonitor.cc::SetSendMessageTask: PushMultiMsg serialize to string error!");
        // 这批消息序列化失败的话可以不要了，以后让客户端主动拉取消息
        return;
    }

    // 调用MessageSender组件的发送消息函数，直接传入MsgCmd对象即可
    MessageSender::Get().FanoutMessage(message::PushBatch, session_msg_str);
}
