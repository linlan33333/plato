#pragma once

#include "grpc/state/state.grpc.pb.h"

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

    std::unique_ptr<State::Stub> stub_;
};