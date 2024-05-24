#include "gateway/workpool.h"
#include "config/gateway.h"

WorkPool::WorkPool()
{    
    pool_ = new ThreadPool(GatewayConfig::Get().GetThreadNumForWorkPool());
}

WorkPool &WorkPool::Get()
{
    static WorkPool pool;
    return pool;
}

WorkPool::~WorkPool()
{
    if (pool_) 
    {
        delete pool_;
    }
}

void WorkPool::Push(std::function<void()> func)
{
    pool_->enqueue(func);
}
