#include "timewheel/time_wheel.h"

TimeWheel::TimeWheel(uint32_t scales, uint32_t scale_unit_ms, const std::string& name)
    : name_(name)
    , current_index_(0)
    , scales_(scales)
    , scale_unit_ms_(scale_unit_ms)
    , slots_(scales)
    , greater_level_tw_(nullptr)
    , less_level_tw_(nullptr) {
}

// 获取当前时间轮执行多久了
int64_t TimeWheel::GetCurrentTime() const {
  int64_t time = current_index_ * scale_unit_ms_;
  // 递归查询小一级时间轮执行到哪个时间点了
  if (less_level_tw_ != nullptr) {
    time += less_level_tw_->GetCurrentTime();
  }

  return time;
}

// 添加任务到当前时间轮数组中
void TimeWheel::AddTimer(TimerPtr timer) {
  int64_t less_tw_time = 0;
  // 获取小一级时间轮已经执行多久了，也就是零头时间，或者说“页内偏移量”
  if (less_level_tw_ != nullptr) {
    less_tw_time = less_level_tw_->GetCurrentTime();
  }
  // 定时器预定触发的时间 + 小一级时间轮已经过去的时间 - 当前系统时间，为什么这么算
  // 因为定时器预定触发的时间 - 当前系统时间 = 还有多久要执行，如果直接那这个值去除以当前时间轮的刻度的话
  // 就相当于默认定时器没有走，比如计算出来还有1小时40分钟要执行，当前时间轮刻度是小时，但是定时器已经执行完1小时30分钟内的所有任务了，是有一个偏移量的，
  // 要是直接把该任务放到第二个格子里，就会导致再过10分钟就会执行该任务，肯定出问题的，所以得加上这个偏移量1小时30分钟，但是这个已经执行的1小时暂时可以
  // 不用加，下面会加，也就是加上current_index_
  int64_t diff = timer->when_ms() + less_tw_time - GetNowTimestamp();

  // If the difference is greater than scale unit, the timer can be added into the current time wheel.
  if (diff >= scale_unit_ms_) {
    size_t n = (current_index_ + diff / scale_unit_ms_) % scales_;
    slots_[n].push_back(timer);
    return;
  }

  // If the difference is less than scale uint, the timer should be added into less level time wheel.
  if (less_level_tw_ != nullptr) {
    less_level_tw_->AddTimer(timer);
    return;
  }

  // If the current time wheel is the least level, the timer can be added into the current time wheel.
  slots_[current_index_].push_back(timer);
}

void TimeWheel::Increase() {
  // Increase the time wheel.
  // 最小时间刻度的时间轮数组上的指针向后移动一格
  ++current_index_;
  if (current_index_ < scales_) {
    return;
  }

  // If the time wheel is full, the greater level time wheel should be increased.
  // The timers in the current slot of the greater level time wheel should be moved into
  // the less level time wheel.
  // 将指针复位到数组起始位置，模拟循环数组的循环效果
  current_index_ = current_index_ % scales_;
  // 更高时间刻度的时间轮数组的指针往后移动
  if (greater_level_tw_ != nullptr) {
    greater_level_tw_->Increase();
    std::list<TimerPtr> slot = std::move(greater_level_tw_->GetAndClearCurrentSlot());
    // 拿到高一级时间刻度的时间轮后，将移动后的数组元素中的所有任务（封装在Timer中）重新映射到当前时间轮数组中
    for (TimerPtr timer : slot) {
      AddTimer(timer);
    }
  }
}

//
std::list<TimerPtr> TimeWheel::GetAndClearCurrentSlot() {
   // 这个中间变量感觉可以用RVO优化机制优化掉，不需要创建这个对象
  std::list<TimerPtr> slot;
  slot = std::move(slots_[current_index_]);
  return slot;
}
