#include "writer/rpc/client/routercaller.h"
#include "common/config/router.h"
#include <grpcpp/grpcpp.h>
#include "routercaller.h"

RouterCaller::RouterCaller()
    : stub_(Router::Router::NewStub(grpc::CreateChannel(RouterServerConfig::Get().GetIp() + ":" +
        std::to_string(RouterServerConfig::Get().GetPort()), grpc::InsecureChannelCredentials())))
{
}

RouterCaller &RouterCaller::Get()
{
    static RouterCaller caller;
    return caller;

}
void RouterCaller::PushMessage(uint64_t user_id, std::string &data)
{
    Router::PushMessageRequest request;
    request.set_userid(user_id);
    request.set_data(data);

    grpc::ClientContext context;
    Router::PushMessageResponse response;

    stub_->PushMessage(&context, request, &response);
}

void RouterCaller::FanoutMessage(std::string &data)
{
    Router::FanoutMessageRequest request;
    request.set_data(data);

    grpc::ClientContext context;
    Router::FanoutMessageResponse response;

    stub_->FanoutMessage(&context, request, &response);
}
