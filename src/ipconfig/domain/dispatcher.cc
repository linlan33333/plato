#include "domain/dispatcher.h"
#include <spdlog/spdlog.h>
#include <algorithm>

void Dispatcher::UpdateEndpoint(Event *event)
{
    // 上写锁，毕竟修改每秒才改一次，大部分情况下是读操作
    std::unique_lock<std::mutex> lock(candidate_table_mutex_);

    std::string key = event->GetKey();
    // 如果是新增网关节点
    if (event->GetType() == EventType::ADDNODE) 
    {
        // 创建新网关终端节点
        Endpoint* endpoint = new Endpoint(event->GetIp(), event->GetPort());
        State s(event->GetConnectionNum(), event->GetMessageBytes());
        // 该设置的信息设置好
        endpoint->UpdateStat(s);
        // 放入大池子里
        candidate_table_.insert({key, endpoint});
        return;
    }

    // 更新网关节点数据
    auto endpoint_iter = candidate_table_.find(key);
    if  (endpoint_iter == candidate_table_.end())
    {
        spdlog::warn("Can\'t find endpoint when updates the endpoint : {}", key);
        return;
    }
    // 根据event对象创建一个新的Stat对象
    State s(event->GetConnectionNum(), event->GetMessageBytes());
    // 更新到endpoint中
    endpoint_iter->second->UpdateStat(s);
}

void Dispatcher::DeleteEndpoint(Event *event)
{
    std::unique_lock<std::mutex> lock(candidate_table_mutex_);

    std::string key = event->GetKey();

    auto endpoint_iter = candidate_table_.find(key);
    if (endpoint_iter != candidate_table_.end())
    {
        // 别忘了内存资源释放
        delete endpoint_iter->second;
        candidate_table_.erase(endpoint_iter);
    }
    else 
    {
        spdlog::warn("Can\'t find target endpoint {} when dispacher delete!", key);
    }
}

std::vector<std::string> Dispatcher::GetCandidateEndpoint()
{
    // 有没有可能有个线程刚把endpoint_top5_历史数据清空，然后切换线程执行该函数，把空数据返回回去？
    // 所以这里得上锁才能返回
    std::shared_lock<std::shared_mutex> lock(endpoint_top5_mutex_);
    return endpoint_top5_;
}

void Dispatcher::Dispatch()
{
    std::vector<Endpoint*> candidates;

    {
        std::unique_lock<std::mutex> lock(candidate_table_mutex_);
        for (auto& item : candidate_table_)
        {
            candidates.push_back(item.second);
        }
    }
    // 全局排序，动静结合的排序策略
    std::sort(candidates.begin(), candidates.end(), [] (Endpoint* a, Endpoint* b) {
        // 优先基于活跃分数进行排序
        if (a->GetActiveScore() > b->GetActiveScore())
        {
            return true;
        }
        // 如果活跃分数相同，则使用静态分数排序
        if (a->GetActiveScore() == b->GetActiveScore())
        {
            return a->GetStaticScore() > b->GetStaticScore();
        }
        return false;
    });

    {
        std::unique_lock<std::shared_mutex> lock(endpoint_top5_mutex_);
        // 先把历史数据清除掉
        endpoint_top5_.clear();

        if (candidates.size() >= 5)
        {
            for (int i = 0; i < 5; i++)
            {
                endpoint_top5_.emplace_back(candidates[i]->GetKey());
            }
        }
        else 
        {
            for (auto& candidate : candidates)
            {
                endpoint_top5_.emplace_back(candidate->GetKey());
            }
        }
    }
}