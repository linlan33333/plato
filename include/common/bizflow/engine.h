#pragma once

#include "bizflow/flow.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <semaphore>

class Flow;
class Graph;

// 这里修改一下Engine类的设计，Engine类只能看到Flow对象，对Flow对象进行管理
// 至于Graph对象则完全交给Flow对象来管理
class Engine
{
public:
    /// @brief 作为整个框架的全局调度类，我想做成单例模式，因为所有的业务创建对应的服务编排DAG后
    /// 都可以放入这个Engine类中，由它同一管理调度。如果不合适，后期再改
    /// @return 
    static Engine& Get();

    /// @brief 添加一个Flow对象进来
    /// @param flow 
    void AddFlow(std::shared_ptr<Flow> flow);
    std::shared_ptr<Flow> GetFlow(std::string& flow_name);

    /// @brief 由于需要限制同时运行的flow数量，这个flow_parallel_num_就得做成信号量那样小于等于0就阻塞线程
    /// 归还信号量
    void IncrFlowParallelNum();
    /// @brief 信号量减一，表示可同时运行的Flow数量减一
    void DecrFlowParallelNum();

    /// @brief 根据任务流Flow的名称创建出一个全新的Graph对象出来
    /// @param flow_name 
    /// @return 
    std::shared_ptr<Graph> CreateDAG(std::string& flow_name);

private:
    Engine();

    Engine(const Engine&) = delete;
    Engine& operator= (const Engine&) = delete;

    /// @brief 所有的业务服务流就存储在这里
    std::unordered_map<std::string, std::shared_ptr<Flow>> flows_;

    /// @brief 设置最多允许几个flow同时运行，根据配置文件初始化值
    /// 这里有一个小小的疑问：线程池已经设置了线程数，按理来说就限制了最多同时运行的flow数量，为什么还要单独设置这个变量
    /// 看后续是怎么使用这个变量的
    std::counting_semaphore flow_parallel_num_;
};