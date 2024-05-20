#pragma once

#include "discovery/zookeeperutil.h"
#include "domain/dispatcher.h"

class Source
{
public:
    Source(Dispatcher* dispatcher);
    ~Source();

    void Init();

    /// @brief 该函数用于获取所有网关节点的数据
    void UpdateEndpointData();

private:
    /// @brief 当zookeeper监听到新节点的添加时触发该回调函数
    void AddEndpoint(zhandle_t* zk_cli, const char* str, const char* data);

    /// @brief 当zookeeper监听到有结点删除时触发该回调函数
    void DelEndpoint(zhandle_t* zk_cli, const char* str);

    ZkClient zk_cli_;

    /// @brief 由于新增节点、更新节点信息等操作都需要将数据传到dispatcher对象中
    /// 该对象目前只能通过main函数传进来，但又似乎耦合性强，如果有什么好的设计模式
    /// 可以解决这个问题，后续会优化
    Dispatcher* dispatcher_;
};