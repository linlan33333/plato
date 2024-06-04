#ifndef TIMER_TASK_H_
#define TIMER_TASK_H_

#include <cstdint>
#include <functional>
#include <memory>

typedef std::function<void()> TaskFunc;

// 将任务封装成该对象，方便区分是哪种类型的任务（一次性执行还是重复执行）
class TimerTask {
public:
  TimerTask(uint32_t id, int64_t when_ms, int64_t interval_ms, const TaskFunc& task);

  void Run();

  uint32_t id() const {
    return id_;
  }

  int64_t when_ms() const {
    return when_ms_;
  }

  bool repeated() const {
    return repeated_;
  }

  void UpdateWhenTime() {
    when_ms_ += interval_ms_;
  }

private:
  uint32_t id_;
  // 任务的回调函数
  TaskFunc task_;
  // 该任务触发的绝对时间
  int64_t when_ms_;
  // 重复执行型任务的重复执行间隔时间
  uint32_t interval_ms_;
  // 标识该任务是否是重复执行型任务
  bool repeated_;
};

using TimerPtr = std::shared_ptr<TimerTask>;

#endif  // TIMER_TASK_H_
