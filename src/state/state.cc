#include "state.h"
#include "timer.h"
#include "cache.h"
#include "rpc/client/gatewaycaller.h"
#include <spdlog/spdlog.h>

ConnectionState::ConnectionState(uint64_t connid, uint32_t did)
    : connid_(connid), did_(did)
{
}

void ConnectionState::SetConnId(uint64_t connid)
{
    connid_ = connid;
}

uint64_t ConnectionState::GetConnId()
{
    return connid_;
}

void ConnectionState::SetDeviceId(uint64_t did)
{
    did_ = did;
}

uint64_t ConnectionState::GetDeviceId()
{
    return did_;
}

void ConnectionState::SetMaxClientId(uint64_t client_id)
{
    max_client_id_ = client_id;
}

uint64_t ConnectionState::GetMaxClientId()
{
    return max_client_id_;
}

void ConnectionState::SetHeartTimerId(uint32_t timerid)
{
    heart_timer_id_ = timerid;
}

uint32_t ConnectionState::GetHeartTimerId()
{
    return heart_timer_id_;
}

void ConnectionState::ResetHeartBeatTimer()
{
    // 想修改该用户的状态得先拿到锁
    std::lock_guard<std::mutex> lck(mtx_);
    // 我们约定设置了定时器时该id不为0，为0时表示未设置定时器
    if (heart_timer_id_ != 0) 
    {
        Timer::Get().Cancel(heart_timer_id_);
        heart_timer_id_ = 0;
    }

    std::cout << "已重置心跳计时器" << std::endl;

    // 设置心跳定时器，五秒后没有心跳就启动断线重连计时器
    // 断线重连有两种情况：一是客户端主动断开，这可能是运营商搞的鬼
    // 其次是客户端不知不觉断开，这可能是网络环境较差等情况
    heart_timer_id_ = Timer::Get().RunAfter(5 * 1000, std::bind(&ConnectionState::ResetReConnTimer, this));
}

void ConnectionState::DeleteHeartBeatTimer()
{
    std::lock_guard<std::mutex> lck(mtx_);
    if (heart_timer_id_ != 0) 
    {
        Timer::Get().Cancel(heart_timer_id_);
        heart_timer_id_ = 0;
    }
}

void ConnectionState::SetReConnTimerId(uint32_t timerid)
{
    reconn_timer_id_ = timerid;
}

uint32_t ConnectionState::GetReConnTimerId()
{
    return reconn_timer_id_;
}

void ConnectionState::ResetReConnTimer()
{
    std::lock_guard<std::mutex> lck(mtx_);

    if (reconn_timer_id_ != 0) 
    {
        Timer::Get().Cancel(reconn_timer_id_);
        reconn_timer_id_ = 0;
    }

    // 因为是没有心跳的情况下启动的心跳计时器，此时心跳计时器已经触发完了，所以这里得重置心跳计时器的id
    // 如果后续有不使用心跳计时器触发重连计时器的方法的话，再修改这块逻辑
    heart_timer_id_ = 0;

    std::cout << "已启动断线重连定时器" << std::endl;

    // 初始化断线重连定时器，10秒内没有重连就清理资源
    reconn_timer_id_ = Timer::Get().RunAfter(10 * 1000, std::bind(&CacheState::ConnLogOut, &(CacheState::Get()), connid_));
}

void ConnectionState::DeleteReConnTimer()
{
    std::lock_guard<std::mutex> lck(mtx_);
    if (reconn_timer_id_ != 0) 
    {
        Timer::Get().Cancel(reconn_timer_id_);
        reconn_timer_id_ = 0;
    }
}

void ConnectionState::SetMsgTimerId(uint32_t timerid)
{
    msg_timer_id_ = timerid;
}

uint32_t ConnectionState::GetMsgTimerId()
{
    return msg_timer_id_;
}

void ConnectionState::DeleteMsgTimer()
{
    std::lock_guard<std::mutex> lck(mtx_);

    if (msg_timer_id_ != 0) 
    {
        Timer::Get().Cancel(msg_timer_id_);
        msg_timer_id_ = 0;
    }
}

void ConnectionState::Close()
{
    std::lock_guard<std::mutex> lck(mtx_);

    // 关闭那三个定时器
    if (heart_timer_id_ != 0)
    {
        // 删除定时器和修改id绑定操作，养成习惯
        Timer::Get().Cancel(heart_timer_id_);
        heart_timer_id_ = 0;
    }

    if (reconn_timer_id_ != 0)
    {
        Timer::Get().Cancel(reconn_timer_id_);
        reconn_timer_id_ = 0;
    }

    if (msg_timer_id_ != 0)
    {
        Timer::Get().Cancel(msg_timer_id_);
        msg_timer_id_ = 0;
    }

    // 一堆业务上的操作现在没学，暂时不管

    // 向gateway发送删除连接的信令
    GatewayCaller::Get().DelConn(connid_, "close connection");
}

bool ConnectionState::CheckUPMsg(uint64_t client_id)
{
    // 就为了锁一行代码去创建lock_guard太傻逼了，这里直接手动上锁
    mtx_.lock();
    bool res = (max_client_id_ + 1 == client_id);
    mtx_.unlock();
    return res;
}

void ConnectionState::AddMaxClientId()
{
    mtx_.lock();
    max_client_id_++;
    mtx_.unlock();
}

void ConnectionState::SetMsgId(uint64_t msg_id)
{
    msg_id_ = msg_id;
}

uint64_t ConnectionState::GetMsgId()
{
    return msg_id_;
}

void ConnectionState::AddMsgId()
{
    mtx_.lock();
    msg_id_++;
    mtx_.unlock();
}
