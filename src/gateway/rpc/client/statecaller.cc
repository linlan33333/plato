#include "rpc/client/statecaller.h"
#include "config/state.h"
#include <spdlog/spdlog.h>
#include <grpcpp/grpcpp.h>

StateCaller::StateCaller()
    : stub_(State::NewStub(grpc::CreateChannel(StateServerConfig::Get().GetIp() + ":" +
            std::to_string(StateServerConfig::Get().GetPort()), grpc::InsecureChannelCredentials())))
{

}

void StateCaller::CancelConn(std::string endpoint, uint64_t connid, std::string data)
{
    // 这个逻辑暂时还没学，先不管
    // 是不是去mainLoop中删掉该连接的有关信息？
}

StateCaller& StateCaller::Get()
{
    static StateCaller caller;
    return caller;
}

void StateCaller::SendMsg(std::string endpoint, uint64_t connid, std::string data)
{
    StateRequest push_req;
    push_req.set_endpoint(endpoint);
    push_req.set_connid(connid);
    push_req.set_data(data);

    grpc::ClientContext context;
    StateResponse resp;

    stub_->SendMsg(&context, push_req, &resp);
}


