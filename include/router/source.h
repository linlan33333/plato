#pragma once

#include "common/discovery/zookeeperutil.h"
#include <string>

/// @brief 该类用于服务发现所有的接入层网关，并调用rpc/client的接口创建对应的stub对象
class Source
{
public:
    void Init();

private:
    /// @brief 当zookeeper监听到新节点的添加时触发该回调函数
    /// 会调用rpc/client的接口创建对应的stub对象
    void AddEndpointStub(zhandle_t* zk_cli, const char* node_name, const char* node_data);

    /// @brief 当zookeeper监听到有结点删除时触发该回调函数
    /// 会调用rpc/client的接口删除对应的stub对象
    void DelEndpointStub(zhandle_t* zk_cli, const char* node_data);

    ZkClient zk_cli_;
};