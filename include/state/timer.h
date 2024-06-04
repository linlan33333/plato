#pragma once

#include "timewheel/time_wheel_scheduler.h"
#include <memory>

// 封装定时器的所有操作
class Timer
{
public:
    static Timer& Get();

    /// @brief 启动定时器线程
    void Init();

    /// @brief 设置定时器任务
    /// @param delay_ms 
    /// @param task 
    /// @return 返回一个定时器任务的标识id，想取消任务的话请传入该id
    uint32_t RunAfter(int64_t delay_ms, const std::function<void()>& task);

    /// @brief 取消定时器任务
    /// @param timer_id 
    void Cancel(uint32_t timer_id);

    void Close();

private:
    Timer();

    // 定时器对象
    std::unique_ptr<TimeWheelScheduler> timer_;
};