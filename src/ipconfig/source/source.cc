#include "source/source.h"
#include <iostream>

void Source::Init()
{
    // 设置回调函数
    zk_cli_.SetChildNodeNumAddCallback(std::function<void(zhandle_t*, const char*, const char*)>(std::bind(&Source::AddEndpoint, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)));
    zk_cli_.SetChildNodeNumDelCallback(std::function<void(zhandle_t*, const char*)>(std::bind(&Source::DelEndpoint, this, std::placeholders::_1, std::placeholders::_2)));
    // 启动注册中心
    zk_cli_.Start();
}

void Source::UpdateEndpointData()
{
    // 从注册中心拉取所有网关节点的最新数据，然后调用Dispatcher类的更新节点方法
    // 但是数据的序列化方式得再想想

}

void Source::AddEndpoint(zhandle_t *zk_cli, const char *node_name, const char *node_data)
{
    std::cout << "添加了节点：" << node_name << std::endl;
    // 这里得把节点数据反序列化之类的，用protobuf还是json再考虑考虑
}

void Source::DelEndpoint(zhandle_t *zk_cli, const char *node_name)
{
    std::string key(node_name);
    auto mh_pos = key.find(':');
    
    Event event(EventType::DELNODE, key.substr(0, mh_pos), key.substr(mh_pos + 1, key.size() - mh_pos));

    // 去ip大池子里删掉这个节点
    dispatcher_->DeleteEndpoint(&event);
}

Source::Source(Dispatcher *dispatcher)
    : dispatcher_(dispatcher)
{
}

Source::~Source()
{
    // 释放资源
    delete dispatcher_;
}