#pragma once

#include "threadpool/ThreadPool.h"
#include <functional>

class WorkPool
{
public:
    // 这个线程池对象我想全局使用，而不仅仅服务于rpc server，后续想想怎么设计
    static WorkPool& Get();
    ~WorkPool();

    void Init(int thread_num);

    /// @brief 将回调函数传进来，然后交给线程池去执行
    /// @param func
    void Push(std::function<void()> func);

private:
    WorkPool() = default;

    WorkPool(const WorkPool& pool) = delete;
    WorkPool& operator= (const WorkPool& pool) = delete;

    // 由于ThreadPool没有默认构造函数，这里只能用指针的形式延后创建对象的时间
    ThreadPool* pool_ = nullptr;
};