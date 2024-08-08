#pragma once

#include "common/grpc/state/state.grpc.pb.h"
#include <spdlog/spdlog.h>
#include <map>
#include <string>

class StateCaller 
{
public:
    static StateCaller& Get();
    
    /// @brief 添加新的state server的stub对象，供Source类使用
    /// @param endpoint 
    void AddStateServerStub(std::string& endpoint);

    /// @brief 删除state server的stub对象，供Source类使用
    /// @param endpoint
    void DelStateServerStub(std::string& endpoint);

    /// @brief 向state server发送消息
    /// @param endpoint state server的ip:port
    /// @param conn_id 
    /// @param data 
    void PushMsgCmd(std::string& endpoint, uint64_t conn_id, std::string& data);

    /// @brief 向所有state server广播消息
    /// @param data
    void FanoutMsgCmd(const std::string& data);
private:
    StateCaller() = default;
    StateCaller(const StateCaller&) = delete;
    StateCaller& operator=(const StateCaller&) = delete;
    /// @brief 这里存储所有state server的stub对象，不用要求state server挂掉的时候能立即感知并删除对应的stub对象
    /// 因为state server挂了无所谓，用户收不到消息后续可以主动拉取消息，如果是gateway挂了导致用户连接转移到
    /// 新的gateway服务器上的话，其配对的state server会向router server注册新连接的，此时会替换掉redis中存储
    /// 的旧连接信息userID到endpoint的映射，所以这是最终一致性的场景，不要求网关机挂了就得立即感知到
    /// key是网关的ip地址，value是state server的stub对象
    std::map<std::string, std::unique_ptr<State::Stub>> stubs_;
};