#include "generateid.h"

GenerateId::GenerateId()
    : last_stamp_(getMilliSeconds())
{
}

uint64_t GenerateId::GetID()
{
    std::lock_guard<std::mutex> lock(mtx_);
    int64_t timeStamp = getMilliSeconds();

    // 时间回退，会导致conn_id生成重复，所以得报错
    if (timeStamp < last_stamp_) 
    {
        throw std::runtime_error("Time is moving backwards, waiting until");
    }

    // 当前1ms内生成序列号，就得自增序列号
    if (last_stamp_ == timeStamp) 
    {
        sequence_ = (sequence_ + 1) & max_sequence_;
        // 16位序列号溢出来，就等到下一毫秒再分配
        if (sequence_ == 0) 
        {
            while (timeStamp <= last_stamp_) 
            {
                timeStamp = getMilliSeconds();
            }
        }
    } 
    else    // 如果与上次分配的时间戳不等，则为了防止可能的时钟漂移现象，必须重新计数
    {
        sequence_ = 0;
    }

    last_stamp_ = timeStamp;
    // 将时间戳减去锚点后左移16位，放到47位时间戳对应的位置上去，然后拼上序列号
    uint64_t id = ((timeStamp - twepoch_) << time_left_) | sequence_;
    // 再拼上第一位的工程版本号
    uint64_t connID = id | (version_ << version_left_);
    return connID;
}

int64_t GenerateId::getMilliSeconds()
{
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return duration.count();
}
