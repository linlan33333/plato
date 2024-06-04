#include "timer.h"

Timer::Timer()
{
    int timer_step_ms = 50;
    timer_ = std::make_unique<TimeWheelScheduler>(timer_step_ms);
    timer_->AppendTimeWheel(60, 1000 * 60, "MinuteTimeWheel");
    timer_->AppendTimeWheel(60, 1000, "SecondTimeWheel");
    timer_->AppendTimeWheel(1000 / timer_step_ms, timer_step_ms,  "SecondTimeWheel");
}

Timer &Timer::Get()
{
    static Timer timer;
    return timer;
}

void Timer::Init()
{
    timer_->Start();
}

uint32_t Timer::RunAfter(int64_t delay_ms, const std::function<void()>& task)
{
    return timer_->CreateTimerAfter(delay_ms, task);
}

void Timer::Cancel(uint32_t timer_id)
{
    timer_->CancelTimer(timer_id);
}

void Timer::Close()
{
    timer_->Stop();
}
