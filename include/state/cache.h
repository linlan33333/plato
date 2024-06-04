#pragma once

#include "state/state.h"
#include <map>
#include <memory>

class CacheState
{
public:

    /// @brief CmdHandler需要用这个对象，ConnectionState也需要用到这个对象，但是conn_to_state_table_应当
    /// 全局保持唯一的一份，那干脆写成单例模式吧
    /// @return 
    static CacheState& Get();

    /// @brief 为某个连接客户端创建并管理连接状态对象
    /// @param connid 
    /// @param conn_state 
    void StoreConnIDState(uint64_t connid, std::shared_ptr<ConnectionState> conn_state);
    void DeleteConnIDState(uint64_t connid);
    std::shared_ptr<ConnectionState> GetConnIDState(uint64_t connid);

    void ConnLogOut(uint64_t connid);

private:
    CacheState() = default;
    CacheState(const CacheState&) = delete;
    CacheState& operator= (const CacheState&) = delete;

    // 这个表需要锁吗？是否存在线程安全问题
    std::map<uint64_t, std::shared_ptr<ConnectionState>> conn_to_state_table_;
};