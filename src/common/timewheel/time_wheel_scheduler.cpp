#include "timewheel/time_wheel_scheduler.h"

static uint32_t s_inc_id = 1;

TimeWheelScheduler::TimeWheelScheduler(uint32_t timer_step_ms)
    : timer_step_ms_(timer_step_ms)
    , stop_(false) {
}

bool TimeWheelScheduler::Start() {
  if (timer_step_ms_ < 50) {
    return false;
  }
  
  if (time_wheels_.empty()) {
    return false;
  }

  // 使用线程实现的，运行线程函数就行了
  thread_ = std::thread(std::bind(&TimeWheelScheduler::Run, this));

  return true;
}

void TimeWheelScheduler::Run() {
  while (true) {
    // 每过一刻度时间该线程唤醒，执行后面的逻辑，注意这种做法会导致周期型任务执行时的时间偏移越来越大，
    // 因为下面的代码执行有一定时间，锁导致的线程切换有一定时间。。。
    // 这里得改进一下，比如每执行若干个时间轮刻度的定时任务后计算一下时间偏移量，然后矫正，后续改一下
    std::this_thread::sleep_for(std::chrono::milliseconds(timer_step_ms_));

    // 对整个时间轮上锁，注意这里有个坑点：执行定时函数时会先拿到锁，如果定时函数里面会执行创建定时任务的话，
    // 就会死锁，因为创建定时任务需要拿到锁，但这里锁已经被抢走了，所以定时任务创建不了，定时函数执行不下去，死锁！！！
    // 所以改进方法是缩小锁粒度，这个锁只是为了确保线程拿到当前刻度的所有定时任务时没有其他线程在同时往当前刻度中删除/插入任务
    // 所以执行当前刻度的定时任务时是不需要锁的，因此减小持有锁范围——只在取定时任务期间上锁
    // std::lock_guard<std::mutex> lock(mutex_);
    // if (stop_) {
    //   break;
    // }

    // // 最小刻度的时间轮指针得往后移动了
    // TimeWheelPtr least_time_wheel = GetLeastTimeWheel();
    // least_time_wheel->Increase();
    // // 拿到当前时间轮格子下的所有任务（任务都被封装成了Timer）
    // std::list<TimerPtr> slot = std::move(least_time_wheel->GetAndClearCurrentSlot());

    if (stop_) {
      break;
    }

    // 最小刻度的时间轮指针得往后移动了
    TimeWheelPtr least_time_wheel = GetLeastTimeWheel();
    least_time_wheel->Increase();

    mutex_.lock();
    // 拿到当前时间轮格子下的所有任务（任务都被封装成了Timer）
    std::list<TimerPtr> slot = std::move(least_time_wheel->GetAndClearCurrentSlot());
    mutex_.unlock();

    for (const TimerPtr& timer : slot) {
      auto it = cancel_timer_ids_.find(timer->id());
      if (it != cancel_timer_ids_.end()) {
        cancel_timer_ids_.erase(it);
        continue;
      }

      timer->Run();
      // 如果是重复执行型任务，就更新下一次执行时间
      if (timer->repeated()) {
        timer->UpdateWhenTime();
        GetGreatestTimeWheel()->AddTimer(timer);
      }
    }
  }
}

void TimeWheelScheduler::Stop() {
  {
    std::lock_guard<std::mutex> lock(mutex_);
    stop_ = true;
  }

  thread_.join();
}

TimeWheelPtr TimeWheelScheduler::GetGreatestTimeWheel() {
  if (time_wheels_.empty()) {
    return TimeWheelPtr();
  }

  return time_wheels_.front();
}

// 返回最小时间刻度的时间轮数组
TimeWheelPtr TimeWheelScheduler::GetLeastTimeWheel() {
  if (time_wheels_.empty()) {
    return TimeWheelPtr();
  }

  return time_wheels_.back();
}

// 不支持乱序放入不同时间粒度的时间轮，只能按时间粒度从大到小的顺序放置
void TimeWheelScheduler::AppendTimeWheel(uint32_t scales, uint32_t scale_unit_ms, const std::string& name) {
  TimeWheelPtr time_wheel = std::make_shared<TimeWheel>(scales, scale_unit_ms, name);
  if (time_wheels_.empty()) {
    time_wheels_.push_back(time_wheel);
    return;
  }

  TimeWheelPtr greater_time_wheel = time_wheels_.back();
  greater_time_wheel->set_less_level_tw(time_wheel.get());
  time_wheel->set_greater_level_tw(greater_time_wheel.get());
  time_wheels_.push_back(time_wheel);
}

uint32_t TimeWheelScheduler::CreateTimerAt(int64_t when_ms, const TaskFunc& task) {
  if (time_wheels_.empty()) {
    return 0;
  }

  std::lock_guard<std::mutex> lock(mutex_);
  ++s_inc_id;
  GetGreatestTimeWheel()->AddTimer(std::make_shared<TimerTask>(s_inc_id, when_ms, 0, task));

  return s_inc_id;
}

uint32_t TimeWheelScheduler::CreateTimerAfter(int64_t delay_ms, const TaskFunc& task) {
  int64_t when = GetNowTimestamp() + delay_ms;
  return CreateTimerAt(when, task);
}

uint32_t TimeWheelScheduler::CreateTimerEvery(int64_t interval_ms, const TaskFunc& task) {
  if (time_wheels_.empty()) {
    return 0;
  }

  std::lock_guard<std::mutex> lock(mutex_);
  ++s_inc_id;
  int64_t when = GetNowTimestamp() + interval_ms;
  GetGreatestTimeWheel()->AddTimer(std::make_shared<TimerTask>(s_inc_id, when, interval_ms, task));

  return s_inc_id;
}

void TimeWheelScheduler::CancelTimer(uint32_t timer_id) {
  std::lock_guard<std::mutex> lock(mutex_);
  cancel_timer_ids_.insert(timer_id);
}
