#pragma once

#include "srpc/gateway/gateway.srpc.h"
#include "workflow/WFFacilities.h"

using namespace srpc;

class GatewayCaller
{
public:
    static GatewayCaller& Get();

    void DelConn(unsigned long long connid, std::string data);

    void Push(unsigned long long connid, std::string data);

private:
    GatewayCaller();
    GatewayCaller(const GatewayCaller&) = delete;
    GatewayCaller& operator= (const GatewayCaller&) = delete;

    void delconn_done(GatewayResponse *response, srpc::RPCContext *context);
    void push_done(GatewayResponse *response, srpc::RPCContext *context);

    Gateway::SRPCClient client_;
};