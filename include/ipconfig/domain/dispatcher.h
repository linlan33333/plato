#pragma once

#include "domain/endpoint.h"
#include "source/event.h"
#include <map>
#include <string>
#include <vector>
#include <mutex>
#include <shared_mutex>

class Dispatcher
{
public:

    /// @brief 添加、更新Endpoint都会调用该方法
    /// @param   
    void UpdateEndpoint(Event* event);

    void DeleteEndpoint(Event* event);

    /// @brief 返回endpoint_top5_
    /// @return 以“ip:port”的形式返回前五个网关节点
    std::vector<std::string> GetCandidateEndpoint();

    /// @brief 该接口对candidate_table_进行排序，得到负载最低的前5个ip，存到endpoint_top5_
    void Dispatch();

private:

    /// @brief 网关节点大池子，等着排序吧
    std::map<std::string, Endpoint*> candidate_table_;
    std::mutex candidate_table_mutex_;

    /// @brief ip config server是每秒从服务注册中心拉取最新数据，因此拉取更新完池子后，在接下来的1秒内
    /// 任意客户端拿到的网关ip top5都是一样的，所以没必要每次客户端请求时就对池子排一次序。因此每次从
    /// 服务注册中心拉取更新完池子后就排序，取top5保存该结果到某个变量中，接下来客户端请求就返回这个数据，
    /// 避免每次请求时还要上读写锁，再排序造成的性能损失。
    std::vector<std::string> endpoint_top5_;
    std::shared_mutex endpoint_top5_mutex_;
};