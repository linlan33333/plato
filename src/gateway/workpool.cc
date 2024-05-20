#include "gateway/workpool.h"

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

void WorkPool::Init(int thread_num)
{
    pool_ = new ThreadPool(thread_num);
}

void WorkPool::Push(std::function<void()> func)
{
    pool_->enqueue(func);
}
