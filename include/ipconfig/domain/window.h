#pragma once

#include "domain/stat.h"
#include <queue>
#include <memory>

#define WINDOWSIZE 5

class Window
{
public:
    /// @brief 将新的Stat对象放到窗口中
    /// @param s 
    void AppendStat(State& s);

    /// @brief 得到整个窗口的平均动态分
    /// @return 
    double GetActiveScore();

    /// @brief 得到整个窗口的平均静态分
    /// @return 
    double GetStaticScore();

private:
    // 我都怕栈内存溢出，还是把对象都放到堆内存上吧
    std::queue<std::unique_ptr<State>> stat_queue_;

    // 当前队列中所有Stat对象的和
    State sum_stat_;
};