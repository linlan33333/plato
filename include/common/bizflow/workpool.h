#pragma once

#include "threadpool/ThreadPool.h"
#include <functional>
#include <memory>

class BizFlowWorkPool
{
public:
    // 这个线程池是bizflow专门使用的，单独定义一个类出来是因为众多Graph对象需要往里面放节点运行，如果定义在Engine类中
    // 所有的Graph还得反向引用到Engine对象上去，个人不是很想这么做，所以单独定义一个专用的线程池类
    static BizFlowWorkPool& Get();

    /// @brief 将回调函数传进来，然后交给线程池去执行
    /// @param func
    void Push(std::function<void()> func);

private:
    BizFlowWorkPool();

    BizFlowWorkPool(const BizFlowWorkPool& pool) = delete;
    BizFlowWorkPool& operator= (const BizFlowWorkPool& pool) = delete;

    std::unique_ptr<ThreadPool> pool_;
};
