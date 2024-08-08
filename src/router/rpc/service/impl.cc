#include "router/rpc/service/impl.h"
#include "common/cache/const.h"
#include "common/cache/rediscli.h"
#include "router/rpc/client/statecaller.h"
#include "router/workpool.h"

grpc::Status RouterRpcServiceImpl::AddRecord(grpc::ServerContext *context, const Router::AddRecordRequest *request, Router::AddRecordResponse *response)
{
    char key[100];
    sprintf(key, cache::LoginSlotSetKey.c_str(), request->userid());
    std::string value = request->endpoint() + "-" + std::to_string(request->connid());

    // 向redis中注册用户userID到did的映射，但是目前没有实现多设备登录，所以暂时是userID到endpoint + connid的映射
    RedisCli::Get().SADD(key, value);

    return grpc::Status::OK;
}
grpc::Status RouterRpcServiceImpl::QueryRecord(grpc::ServerContext *context, const Router::QueryRecordRequest *request, Router::QueryRecordResponse *response)
{
    return grpc::Status::OK;
}

grpc::Status RouterRpcServiceImpl::DelRecord(grpc::ServerContext *context, const Router::DelRecordRequest *request, Router::DelRecordResponse *response)
{
    char key[100];
    sprintf(key, cache::LoginSlotSetKey.c_str(), request->userid());

    std::string value = request->endpoint() + "-" + std::to_string(request->connid());
    std::vector<std::string> values{value};
    RedisCli::Get().SREM(key, values);

    return grpc::Status::OK;
}

grpc::Status RouterRpcServiceImpl::PushMessage(grpc::ServerContext *context, const Router::PushMessageRequest *request, Router::PushMessageResponse *response)
{
    char key[100];
    sprintf(key, cache::LoginSlotSetKey.c_str(), request->userid());

    // 查到该用户userID的所有设备的endpoint，但目前还没有做多设备登录的功能，所以这里拿到的直接就是用户的endpoint + connid
    std::unordered_set<std::string> endpoints = RedisCli::Get().SmembersStrSlice(key);
    for (auto& endpoint_connid_str : endpoints)
    {
        // 先提取出网关的ip
        std::string endpoint = endpoint_connid_str.substr(0, endpoint_connid_str.find("-"));
        // 再拿到connid
        uint64_t conn_id = std::stoull(endpoint_connid_str.substr(endpoint_connid_str.find("-") + 1));
        std::string data = request->data();
        // 由于用户可能有多台设备在线，需要全部推送过去，所以不能串行推送，得并行开多线程推送
        WorkPool::Get().Push([endpoint, conn_id, data] () mutable {
            StateCaller::Get().PushMsgCmd(endpoint, conn_id, data);
        });
    }
    return grpc::Status::OK;
}

grpc::Status RouterRpcServiceImpl::FanoutMessage(grpc::ServerContext *context, const Router::FanoutMessageRequest *request, Router::FanoutMessageResponse *response)
{
    // 向所有state server扇出消息
    StateCaller::Get().FanoutMsgCmd(request->data());

    return grpc::Status::OK;
}
