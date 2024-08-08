#include "domain/user/workpool.h"
#include "common/config/router.h"

WorkPool::WorkPool()
{    
    pool_ = new ThreadPool(RouterServerConfig::Get().GetThreadNumForWorkPool());
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
