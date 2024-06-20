#include "cache.h"
#include "rpc/client/gatewaycaller.h"
#include "cache/rediscli.h"
#include "config/state.h"
#include "cache/const.h"
#include "router/table.h"
#include "workpool.h"
#include <spdlog/spdlog.h>

CacheState &CacheState::Get()
{
    static CacheState state;
    return state;
}

void CacheState::Init()
{
    // 初始化redis连接
    RedisCli::Get().Init();
    // 初始化router
    // 。。。。。

    // 拿到该state server所有的连接所在的set集合范围，从中读取分布式存储的连接connid信息
    std::pair<int, int> login_slot_range = StateServerConfig::Get().GetStateServerLoginSlotRange();
    // 区间左闭右闭全部使用
    for (int i = login_slot_range.first; i <= login_slot_range.second; i++) {
        char set_name[100];
        sprintf(set_name, cache::LoginSlotSetKey.c_str(), i);
        // 异步并行处理，去检查该登陆槽中有没有连接connid信息，如果有，说明该链接可能还与gateway连着，需要重新设置心跳定时器
        WorkPool::Get().Push([set_name, this] () {
            std::unordered_set<std::string> login_slots = RedisCli::Get().SmembersStrSlice(set_name);
            for (auto& login_slot : login_slots) {
                std::pair<uint64_t, uint64_t> did_connid_pair = LoginSlotUnmarshal(login_slot);
                // 拿到connid后需要恢复心跳定时器，还需要查看飞行队列中有没有最新消息没推送，如果有就推送并开启消息定时器
                // 这些都交给ConnReLogin函数去做
                ConnReload(did_connid_pair.first, did_connid_pair.second);
            }
        });
    }
}

void CacheState::StoreConnIDState(uint64_t connid, std::shared_ptr<ConnectionState> conn_state)
{
    conn_to_state_table_.insert({connid, conn_state});
}

void CacheState::DeleteConnIDState(uint64_t connid)
{
    conn_to_state_table_.erase(connid);
}

std::shared_ptr<ConnectionState> CacheState::GetConnIDState(uint64_t connid)
{
    auto conn_state_pair = conn_to_state_table_.find(connid);
    if (conn_state_pair == conn_to_state_table_.end()) 
    {
        spdlog::warn("CacheState.cc::GetConnIDState: Find connection state object failed!");
        return nullptr;
    }

    return conn_state_pair->second;
}

uint64_t CacheState::ConnLogOut(uint64_t connid)
{
    std::shared_ptr<ConnectionState> state = GetConnIDState(connid);
    uint64_t did = state->GetDeviceId();
    if (state != nullptr)
    {
        // 这里面会向gateway发送断开连接的rpc请求
        state->Close();

        // 调用router的接口去redis中删除该用户的登录信息
        Router::Get().DelRecord(did);

        // 移除该连接对象的状态
        DeleteConnIDState(connid);

        return did;
    }

    return -1;
}

bool CacheState::ReConnection(uint64_t old_connid, uint64_t new_connid)
{
    // 重连需要执行登出逻辑，因为需要去redis中把connid信息删掉，而这一步是在登出逻辑中做的
    uint64_t did = ConnLogOut(old_connid);
    if (did == -1) 
    {
        spdlog::warn("CacheState.cc::ReConnection: Logout failed! Can\'t find connection object!");
        return false;
    }
    // 然后执行登录操作，将new_connid信息注册到redis中
    ConnLogin(did, new_connid);
    return true;
}

void CacheState::ResetConnTimer(uint64_t connid)
{
    std::shared_ptr<ConnectionState> state = GetConnIDState(connid);
    if (state != nullptr)
    {
        state->ResetHeartBeatTimer();
    }
}

std::string CacheState::LoginSlotMarshal(uint64_t did, uint64_t connid)
{
    std::string login_slot;
    login_slot += std::to_string(did);
    login_slot.push_back('|');
    login_slot += std::to_string(connid);

    return login_slot;
}

std::pair<uint64_t, uint64_t> CacheState::LoginSlotUnmarshal(const std::string &login_slot)
{
    int pos = login_slot.find('|');
    std::string did_str = login_slot.substr(0, pos);
    std::string connid_str = login_slot.substr(pos + 1, login_slot.size());
    
    return std::make_pair(std::stoull(did_str), std::stoull(connid_str));
}

std::string CacheState::GetLoginSlotKey(uint64_t connid)
{
    // 拿到存储connid的set集合名称范围
    std::pair<int, int> login_slot_range = StateServerConfig::Get().GetStateServerLoginSlotRange();
    int range = login_slot_range.second - login_slot_range.first + 1;

    // 对connid哈希取余，确定它应该存储到哪个set中
    int slot = connid % range;
    char set_name[1024];
    sprintf(set_name, cache::LoginSlotSetKey.c_str(), slot);

    return set_name;
}

void CacheState::ConnLogin(uint64_t did, uint64_t connid)
{
    // 创建一个ConnectionState对象，同时设置心跳定时器
    std::shared_ptr<ConnectionState> conn_state_ptr = NewConnState(did, connid);

    // 初始化登录槽，准备好持久化到redis中的信息并存储
    std::string login_slot = GetLoginSlotKey(connid);
    std::cout << "登录槽是: " << login_slot << std::endl;
    std::string did_connid_meta = LoginSlotMarshal(did, connid);
    // 把connid信息存储到登录槽中
    RedisCli::Get().SADD(login_slot, did_connid_meta);

    // 添加路由记录，将该用户的登录消息存到redis中，方便业务服务器反查该用户在哪台机器上
    std::string endpoint = StateServerConfig::Get().GetIp() + ":" + std::to_string(StateServerConfig::Get().GetPort());
    Router::Get().AddRecord(did, endpoint, connid);

    // TODO 上行消息中的 max_client_id 初始化，现在相当于生命周期在conn维度，后面重构sdk时会调整到会话维度

    // 存储ConnectionState对象到大map表里
    conn_to_state_table_.insert({connid, conn_state_ptr});
}

void CacheState::ConnReload(uint64_t did, uint64_t connid)
{
    // 根据connid创建对应的ConnectionState对象，这一步中会恢复心跳定时器
    std::shared_ptr<ConnectionState> conn_state = NewConnState(did, connid);
    // 往大map中存储一下ConnectionState
    StoreConnIDState(connid, conn_state);

    // 去飞行队列中查看有没有最新的消息，如果有需要推送 + 开启定时器
    std::unique_ptr<message::PushMsg> push_msg_ptr = GetLastMsg(connid);
    if (push_msg_ptr != nullptr) 
    {
        // 这里为什么只是恢复定时器而不推送最新消息呢？只恢复定时器倒也不是不行，用户会多等1个超时时间才会收到消息
        // 个人感觉直接调用CmdHandler::RePush方法可以一次性完成获取最新消息、发送最新消息、设置定时器三步会不会更好
        // 用户不用多等待一个超时时间收到消息
        conn_state->ResetMsgTimer(push_msg_ptr->sessionid(), push_msg_ptr->msgid());
    }
}

std::shared_ptr<ConnectionState> CacheState::NewConnState(uint64_t did, uint64_t connid)
{
    // 创建ConnectionState对象
    std::shared_ptr<ConnectionState> conn_state = std::make_shared<ConnectionState>(connid, did);
    // 设置/恢复心跳定时器
    conn_state->ResetHeartBeatTimer();

    return conn_state;
}

bool CacheState::CompareAndIncrClientID(uint64_t connid, uint64_t old_max_clientid)
{
    int slot_key = GetConnStateSlot(connid);
    char max_client_id_key[100];
    sprintf(max_client_id_key, cache::MaxClientIDKey.c_str(), slot_key, connid);

    // 组织一下传给lua脚本的参数
    std::vector<std::string> keys;
    keys.emplace_back(max_client_id_key);
    std::vector<long long> args = {
        static_cast<long long>(old_max_clientid),
        static_cast<long long>(cache::TTL7D.count())
    };
    // 执行lua脚本
    int res = RedisCli::Get().RunLuaInt<std::string, long long>(LuaScriptName::LuaCompareAndIncrClientID, keys, args);
    // 打印日志，这里直接控制台输出了，关于日志怎么整后续再改
    spdlog::info("CacheState.cc::CompareAndIncrClientID: Run lua script");

    // lua脚本执行成功会返回1，失败 返回-1，以此判断执行是否成功
    return res > 0;
}

bool CacheState::AppendLastMsg(uint64_t connid, message::PushMsg &push_msg, std::string &push_msg_str)
{
    std::shared_ptr<ConnectionState> conn_state = GetConnIDState(connid);
    if (conn_state == nullptr)
    {
        spdlog::warn("CacheState.cc::AppendLastMsg: Can\'t find target ConnectionState object!");
        return false;
    }

    int slot_key = GetConnStateSlot(connid);
    char last_msg_key[100];
    sprintf(last_msg_key, cache::LastMsgKey.c_str(), slot_key, connid);
    // 创建元信息锁、设置重传定时器、存储消息到redis飞行队列
    // TODO 现在假设一个链接只有一个会话，后面再讲IMserver，会进行重构
    conn_state->AppendMsg(last_msg_key, push_msg.sessionid(), push_msg.msgid(), push_msg_str);

    return true;
}

std::unique_ptr<message::PushMsg> CacheState::GetLastMsg(uint64_t connid)
{
    int slot_key = GetConnStateSlot(connid);
    // 该连接的最后的消息的key，这个最后的消息和connid存储在同一个slot中，而且存储形式是string，key就是它
    // value是PushMsg反序列化后的二进制数据
    char last_msg_key[100];
    sprintf(last_msg_key, cache::LastMsgKey.c_str(), slot_key, connid);

    std::string msg_str = RedisCli::Get().GetBytes(last_msg_key);
    // 有最后的消息没推送到客户端手上，那就需要恢复定时器，推送消息
    if (msg_str.size() != 0) 
    {
        std::unique_ptr<message::PushMsg> push_msg_ptr = std::make_unique<message::PushMsg>();
        if (!push_msg_ptr->ParseFromString(msg_str)) 
        {
            spdlog::warn("cache.cc::GetLastMsg: PushMsg parse failed!");
        }

        return push_msg_ptr;
    }

    // 飞行队列中没有要推送的消息，那就返回个空指针
    return std::unique_ptr<message::PushMsg> ();
}

void CacheState::AckLastMsg(uint64_t connid, uint64_t sessionid, uint64_t msgid)
{
    std::shared_ptr<ConnectionState> conn_state = GetConnIDState(connid);
    if (conn_state == nullptr)
    {
        spdlog::warn("CacheState.cc::AckLastMsg: Can\'t find target ConnectionState object!");
        return;
    }

    // 删除定时器和飞行队列中的消息
    conn_state->AckLastMsg(sessionid, msgid);
}

uint64_t CacheState::GetConnStateSlot(uint64_t connid)
{
    int slot_list_range = StateServerConfig::Get().GetStateServerLoginSlotRange().second + 1;

    return connid % slot_list_range;
}
