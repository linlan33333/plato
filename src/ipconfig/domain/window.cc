#include "domain/window.h"
#include <spdlog/spdlog.h>

void Window::AppendStat(State &s)
{
    if (stat_queue_.size() == 5) 
    {
        // 减去即将被删除的state的那些数值：吞吐量、连接数
	    // 为什么这么算：因为这么算只需要减去老的，加上新的只要两次操作，如果把窗口里的值从头加还得操作5次
        sum_stat_ -= *stat_queue_.front();
        stat_queue_.pop();
        stat_queue_.push(std::make_unique<State>(s));
        sum_stat_ += s;

        return;
    }

    sum_stat_ += s;
    stat_queue_.push(std::make_unique<State>(s));
}

double Window::GetActiveScore()
{
    if (stat_queue_.size() == 0)
    {
        spdlog::warn("There is no stat object in window!");
        return 0;
    }
    // 拷贝一个sum_stat_的副本再操作，因为Avg方法会直接修改Stat对象里面的值，就破坏了sum_stat_
    State temp(sum_stat_);
    temp.Avg(stat_queue_.size());

    return temp.CalculateActiveScore();
}

double Window::GetStaticScore()
{
    // 为防止除以0，先做个判断
    if (stat_queue_.size() == 0)
    {
        spdlog::warn("There is no stat object in window!");
        return 0;
    }
    State temp(sum_stat_);
    temp.Avg(stat_queue_.size());

    return temp.CalculateStaticScore();
}
