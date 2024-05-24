#include <chrono>
#include <mutex>

using namespace std;

// 该类专门用来生成唯一id的，哪需要就直接用即可
class GenerateId
{
public:
    static GenerateId& Get();

    uint64_t GetID();

private:
    GenerateId();

    GenerateId(const GenerateId&) = delete;
    GenerateId& operator= (const GenerateId&) = delete;

    int64_t getMilliSeconds(); 

    /// 记录上一次生成id时的时间戳，为了防止系统时间倒退的
    int64_t last_stamp_ = 0;
    /// 记录同一秒内生成的id的序列号最大值到多少
    int64_t sequence_ = 0;

    /// GetID函数是临界区，所以得抢这把锁
    std::mutex mtx_;

    /// 想调整编码就直接调整这些参数，就不往配置文件里面写了
    const uint64_t version_ = 0;
    const uint64_t sequence_bits_ = 16;
    const int64_t max_sequence_ = (1LL << sequence_bits_) - 1;
    const uint8_t time_left_ = sequence_bits_;
    const uint8_t version_left_ = 63;
    // 2024-05-20 08:00:00 CST 转化的Unix时间戳
    const int64_t twepoch_ = 1716163200000;
};