#include "bizflow/workpool.h"
#include "config/bizflow.h"

BizFlowWorkPool::BizFlowWorkPool()
    : pool_(std::make_unique<ThreadPool>(BizFlowConfig::Get().GetWorkSize()))
{
}

BizFlowWorkPool &BizFlowWorkPool::Get()
{
    static BizFlowWorkPool pool;
    return pool;
}

void BizFlowWorkPool::Push(std::function<void()> func)
{
    pool_->enqueue(func);
}