#include "cache.h"
#include "rpc/client/gatewaycaller.h"
#include <spdlog/spdlog.h>

CacheState &CacheState::Get()
{
    static CacheState state;
    return state;
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

void CacheState::ConnLogOut(uint64_t connid)
{
    std::shared_ptr<ConnectionState> state = GetConnIDState(connid);
    if (state != nullptr)
    {
        // 这里面会向gateway发送断开连接的rpc请求
        state->Close();
        // 移除该连接对象的状态
        DeleteConnIDState(connid);
    }
}
