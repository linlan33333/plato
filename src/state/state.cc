#include "state.h"
#include "timer.h"
#include "cache.h"
#include "rpc/client/gatewaycaller.h"
#include "cache/rediscli.h"
#include "cache/const.h"
#include "cmdhandler.h"
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

    spdlog::info("Connection has start reconnection timer");

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

uint32_t ConnectionState::GetMsgTimerId()
{
    return msg_timer_id_;
}

void ConnectionState::ResetMsgTimer(uint64_t sessionid, uint64_t msgid)
{
    std::lock_guard<std::mutex> lck(mtx_);
    if (msg_timer_id_ != 0) 
    {
        Timer::Get().Cancel(msg_timer_id_);
        msg_timer_id_ = 0;
    }

    // 存储该msgTimer的元信息，防止老旧消息的ACK消息把该msg的定时器给取消了
    SetMsgTimerLock(sessionid, msgid);
    // 设置定时器，100毫秒之后重发一次
    // 注意：如果state server重启后发现某个连接的飞行队列有没推送的消息，会调用该方法
    // 但是调用该方法可以看到并没有立即推送消息，所以用户得等待一个超时时间后触发RePush函数才能收到消息
    msg_timer_id_ = Timer::Get().RunAfter(100, std::bind(&CmdHandler::RePush, &CmdHandler::Get(), connid_));
}

void ConnectionState::DeleteMsgTimer(std::string &msg_timer_lock)
{
    std::lock_guard<std::mutex> lck(mtx_);

    // 比较元信息锁，相同才删掉定时器
    if (msg_timer_lock == msg_timer_lock_ && msg_timer_id_ != 0)
    {
        Timer::Get().Cancel(msg_timer_id_);
        msg_timer_id_ = 0;
        msg_timer_lock_.clear();
    }
}

void ConnectionState::SetMsgTimerLock(uint64_t sessionid, uint64_t msgid)
{
    msg_timer_lock_.clear();
    msg_timer_lock_ += std::to_string(sessionid) + "_" + std::to_string(msgid);
}

std::string ConnectionState::GetMsgTimerLock()
{
    return msg_timer_lock_;
}

void ConnectionState::AppendMsg(std::string last_msg_key, uint64_t sessionid, uint64_t msgid, std::string &push_msg_str)
{
    // 上锁，确保这三步操作是原子性操作
    std::lock_guard<std::mutex> lck(mtx_);

    // 创建元信息锁
    SetMsgTimerLock(sessionid, msgid);

    // 重新设置重传定时器，注意这里不要直接调用ResetMsgTimer方法，会死锁
    if (msg_timer_id_ != 0)
    {
        Timer::Get().Cancel(msg_timer_id_);
        msg_timer_id_ = 0;
    }
    msg_timer_id_ = Timer::Get().RunAfter(100, std::bind(&CmdHandler::RePush, &CmdHandler::Get(), connid_));

    // 给redis飞行队列存储最新消息
    RedisCli::Get().SetBytes(last_msg_key, push_msg_str, cache::TTL7D);

    std::cout << "飞行队列中添加数据, key: " << last_msg_key << std::endl;
}

void ConnectionState::AckLastMsg(uint64_t sessionid, uint64_t msgid)
{
    std::lock_guard<std::mutex> lck(mtx_);
    std::string timer_lock = std::to_string(sessionid) + "_" + std::to_string(msgid);
    if (msg_timer_lock_ == "" || timer_lock != msg_timer_lock_)
    {
        return;
    }

    // 拿到存储最新消息的key
    int slot_key = CacheState::Get().GetConnStateSlot(connid_);
    char last_msg_key[100];
    sprintf(last_msg_key, cache::LastMsgKey.c_str(), slot_key, connid_);
    // 去redis的飞行队列中删除该消息
    std::vector<std::string> keys({last_msg_key});
    RedisCli::Get().Del(keys);

    // 删掉定时器
    Timer::Get().Cancel(msg_timer_id_);
    msg_timer_id_ = 0;
    msg_timer_lock_.clear();
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

	// TODO 这里如何保证事务性，值得思考一下，或者说有没有必要保证：个人觉得没必要，因为connid是不可复用的，早删晚删都不会有影响
	// TODO 这里也可以使用lua或者pipeline 来尽可能合并两次redis的操作 通常在大规模的应用中这是有效的
	// TODO 这里是要好好思考一下，网络调用次数的时间&空间复杂度的
    std::string slot_key = CacheState::Get().GetLoginSlotKey(connid_);
    std::string did_connid_meta = CacheState::Get().LoginSlotMarshal(did_, connid_);
    std::vector<std::string> values({did_connid_meta});
    // 删掉connid信息
    RedisCli::Get().SREM(slot_key, values);

    int redis_slot = CacheState::Get().GetConnStateSlot(connid_);
    char max_client_id_key[100];
    sprintf(max_client_id_key, cache::MaxClientIDKey.c_str(), redis_slot, connid_); 
    values.clear();
    values.emplace_back(max_client_id_key);
    // 删掉max_client_id
    RedisCli::Get().Del(values);

    // router组件的相关操作，删掉did的记录
    // 。。。。。。

    char last_msg_key[100];
    sprintf(last_msg_key, cache::LastMsgKey.c_str(), redis_slot, connid_);
    values.clear();
    values.emplace_back(max_client_id_key);
    // 删掉last_msg
    RedisCli::Get().Del(values);

    // 向gateway发送删除连接的信令
    GatewayCaller::Get().DelConn(connid_, "close connection");
}

void ConnectionState::SetMsgId(uint64_t msgid)
{
    msg_id_ = msgid;
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
