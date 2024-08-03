#include "flowcontroller.h"
#include "common/config/messagedomain.h"
#include "timer.h"

FlowController &FlowController::Get()
{
    static FlowController controller;
    return controller;
}

void FlowController::AddMessageAndCheckFlow(uint64_t session_id, uint64_t message_id, std::string &msg)
{
    auto monitor_pair = session_flow_monitors_.find(session_id);

    // 当前存在这个超大群聊的监视器对象
    if (monitor_pair != session_flow_monitors_.end())
    {
        // 往对应的session监视器对象中添加消息
        monitor_pair->second->PushMessage(message_id, msg);
        // 判断是否需要进行协议降级
        if (monitor_pair->second->CheckProtocolDowngrade()) 
        {
            monitor_pair->second->ProtocolDowngrade();
        }

        return;
    }

    // 当前不存在这个超大群聊的监视对象，那么就需要创建对应的监视器对象了
    // 写map表就需要加锁了，平时读就不需要，这么麻烦是为了平时读的时候提高并发量
    std::lock_guard<std::mutex> lck(mtx_);

    // 为了防止重复添加导致之前的监视器对象被顶替，造成消息丢失，所以这里得再判断一遍是否有别的线程抢先创建过
    if (session_flow_monitors_.find(session_id) != session_flow_monitors_.end())
    {
        // 往对应的session监视器对象中添加消息
        monitor_pair->second->PushMessage(message_id, msg);
        // 判断是否需要进行协议降级，其实可以不判断，因为刚创建的容器没几条消息，不可能触发协议回退的
        if (monitor_pair->second->CheckProtocolDowngrade()) 
        {
            monitor_pair->second->ProtocolDowngrade();
        }

        return;
    }

    std::shared_ptr<FlowMonitor> flow_monitor_ptr(std::make_shared<FlowMonitor>());
    // 往对应的session监视器对象中添加消息
    flow_monitor_ptr->PushMessage(message_id, msg);

    // 添加该监视器对象
    session_flow_monitors_.emplace(std::make_pair(session_id, flow_monitor_ptr));

    // 向定时器注册定时发送消息的任务
    monitor_pair->second->SetTimerId(Timer::Get().RunAfter(MessageDomainConfig::Get().GetSuperSessionPushInterval(), 
        std::bind(FlowMonitor::SetSendMessageTask, flow_monitor_ptr)));
}
