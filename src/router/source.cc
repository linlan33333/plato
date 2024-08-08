#include "router/source.h"
#include "router/rpc/client/statecaller.h"
#include <spdlog/spdlog.h>

void Source::Init()
{
    // 设置回调函数
    zk_cli_.SetChildNodeNumAddCallback(std::function<void(zhandle_t*, const char*, const char*)>(std::bind(&Source::AddEndpointStub, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)));
    zk_cli_.SetChildNodeNumDelCallback(std::function<void(zhandle_t*, const char*)>(std::bind(&Source::DelEndpointStub, this, std::placeholders::_1, std::placeholders::_2)));
    
    std::string monitor_znode_path = "plato/state";
    zk_cli_.SetMonitorNodePath(monitor_znode_path);
    
    // 连接注册中心
    zk_cli_.Start();
}

void Source::AddEndpointStub(zhandle_t *zk_cli, const char *node_name, const char* node_data)
{
    spdlog::info("Source.cc::AddEndpointStub: New gateway endpoint {} create!", node_name);
    std::string endpoint(node_data);
    StateCaller::Get().AddStateServerStub(endpoint);
}

void Source::DelEndpointStub(zhandle_t *zk_cli, const char *node_data)
{
    spdlog::info("Source.cc::DelEndpointStub: Gateway endpoint {} delete!", node_data);
    std::string endpoint(node_data);
    StateCaller::Get().DelStateServerStub(endpoint);
}