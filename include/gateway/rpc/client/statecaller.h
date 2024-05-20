#pragma once

#include "srpc/state/state.srpc.h"
#include "workflow/WFFacilities.h"

using namespace srpc;

class StateCaller
{
public:
    static StateCaller& Get();

    void CancelConn(std::string endpoint, unsigned long long connid, std::string data);

    void SendMsg(std::string endpoint, unsigned long long connid, std::string data);

private:
    StateCaller();

    StateCaller(const StateCaller&) = delete;
    StateCaller& operator= (const StateCaller&) = delete;

    void cancelconn_done(StateResponse *response, srpc::RPCContext *context);

    void sendmsg_done(StateResponse *response, srpc::RPCContext *context);

    State::SRPCClient client_;
};