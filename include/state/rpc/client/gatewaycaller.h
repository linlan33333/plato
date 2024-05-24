#pragma once

#include "grpc/gateway/gateway.grpc.pb.h"
#include <string>


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

    std::unique_ptr<Gateway::Stub> stub_;
};
