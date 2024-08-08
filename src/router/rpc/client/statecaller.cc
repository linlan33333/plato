#include "router/rpc/client/statecaller.h"
#include "common/idl/message/message.pb.h"
#include <grpcpp/grpcpp.h>

StateCaller& StateCaller::Get()
{
    static StateCaller caller;
    return caller;
}

void StateCaller::AddStateServerStub(std::string &endpoint)
{
    stubs_.emplace(std::make_pair(endpoint, std::make_unique<State::Stub>(State::NewStub(grpc::CreateChannel(endpoint, grpc::InsecureChannelCredentials())))));
}

void StateCaller::DelStateServerStub(std::string &endpoint)
{
    auto pos = stubs_.find(endpoint);
    if (pos == stubs_.end())
    {
        spdlog::warn("StateCaller.cc::AddStateServerStub: Endpoint not found!");
        return;
    }

    stubs_.erase(pos);
}

void StateCaller::PushMsgCmd(std::string& endpoint, uint64_t conn_id, std::string& data)
{
    auto pos = stubs_.find(endpoint);
    if (pos == stubs_.end())
    {
        spdlog::error("StateCaller.cc::PushMsgCmd: Endpoint not found! Can\'t push msg to state server!");
        return;
    }

    grpc::ClientContext context;
    StateRequest request;
    request.set_endpoint(endpoint);
    request.set_connid(conn_id);
    request.set_data(data);
    StateResponse response;
    // 对于消息来说是可丢失的，所以直接推送即可，不需要管state server会不会收到
    pos->second->SendMsg(&context, request, &response);
}

void StateCaller::FanoutMsgCmd(const std::string &data)
{
    for (auto& stub_pair : stubs_)
    {
        grpc::ClientContext context;
        StateRequest request;
        request.set_data(data);
        StateResponse response;
        stub_pair.second->SendMsg(&context, request, &response);
    }
}