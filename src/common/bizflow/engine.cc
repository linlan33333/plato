#include "bizflow/engine.h"
#include "config/bizflow.h"
#include "bizflow/workpool.h"
#include <spdlog/spdlog.h>

Engine::Engine() 
    : flow_parallel_num_(BizFlowConfig::Get().GetFlowParallelNUm())
{   
    // 初始化一下这个专用线程池
    BizFlowWorkPool::Get();
}

Engine &Engine::Get()
{
    static Engine engine;
    return engine;
}

void Engine::AddFlow(std::shared_ptr<Flow> flow)
{
    flows_.emplace(flow->GetName(), flow);
}

std::shared_ptr<Flow> Engine::GetFlow(std::string &flow_name)
{
    auto flow_pair = flows_.find(flow_name);
    if (flow_pair == flows_.end()) 
    {
        spdlog::warn("Engine.cc::GetFlow: Can\'t find target flow from name!");
        return std::shared_ptr<Flow> ();
    }

    return flow_pair->second;
}

void Engine::IncrFlowParallelNum()
{
    flow_parallel_num_.release();
}

void Engine::DecrFlowParallelNum()
{
    flow_parallel_num_.acquire();
}

std::shared_ptr<Graph> Engine::CreateDAG(std::string &flow_name)
{
    auto flow_pair = flows_.find(flow_name);
    if (flow_pair == flows_.end()) 
    {
        spdlog::warn("Engine.cc::GetFlow: Can\'t find target flow from name!");
        return std::unique_ptr<Graph> ();
    }

    // 构建Graph，返回Graph对象指针
    // 因为我们支持从 Engine 对象中直接拿到一个全新的Graph对象，该Graph对象中的所有节点全部都是初始状态，
    // 所以BuildGraph函数就需要重新搭建一个Graph出来，因为不能复用同一个旧的Graph对象，那里面有许多上次运行后的残存数据
    // 所以搭图的逻辑就得放在这个BuildGraph函数中
    return flow_pair->second->BuildGraph();
}
