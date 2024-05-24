#include "rpc/client/gatewaycaller.h"
#include "config/gateway.h"
#include <spdlog/spdlog.h>
#include <grpcpp/grpcpp.h>

GatewayCaller::GatewayCaller()
    : stub_(Gateway::NewStub(grpc::CreateChannel(GatewayConfig::Get().GetIp() + ":" + std::to_string(GatewayConfig::Get().GetPortForRPCService()), grpc::InsecureChannelCredentials())))
{

}

GatewayCaller &GatewayCaller::Get()
{
    static GatewayCaller caller;
    return caller;
}

void GatewayCaller::DelConn(unsigned long long connid, std::string data)
{
    GatewayRequest delconn_req;
    delconn_req.set_connid(connid);
    delconn_req.set_data(data);

    grpc::ClientContext context;
    GatewayResponse resp;

    stub_->DelConn(&context, delconn_req, &resp);
}

void GatewayCaller::Push(unsigned long long connid, std::string data)
{
    GatewayRequest push_req;
    push_req.set_connid(connid);
    push_req.set_data(data);

    grpc::ClientContext context;
    GatewayResponse resp;

    stub_->Push(&context, push_req, &resp);
}
