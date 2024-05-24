#include "utils/generateid.h"

GenerateId::GenerateId()
    : last_stamp_(getMilliSeconds())
{
}

GenerateId &GenerateId::Get()
{
    static GenerateId gen;
    return gen;
}

uint64_t GenerateId::GetID()
{
    std::lock_guard<std::mutex> lock(mtx_);
    int64_t timeStamp = getMilliSeconds();

    if (timeStamp < last_stamp_) {
        throw std::runtime_error("Time is moving backwards, waiting until");
    }

    if (last_stamp_ == timeStamp) {
        sequence_ = (sequence_ + 1) & max_sequence_;
        if (sequence_ == 0) {
            while (timeStamp <= last_stamp_) {
                timeStamp = getMilliSeconds();
            }
        }
    } else {
        sequence_ = 0;
    }

    last_stamp_ = timeStamp;

    uint64_t id = ((timeStamp - twepoch_) << time_left_) | sequence_;
    uint64_t connID = id | (version_ << version_left_);
    return connID;
}

int64_t GenerateId::getMilliSeconds()
{
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return duration.count();
}
