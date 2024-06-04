#pragma once

#include "grpc/gateway/gateway.grpc.pb.h"
#include <string>


class GatewayCaller
{
public:
    static GatewayCaller& Get();

    void DelConn(uint64_t connid, std::string data);

    void Push(uint64_t connid, std::string data);

private:
    GatewayCaller();
    GatewayCaller(const GatewayCaller&) = delete;
    GatewayCaller& operator= (const GatewayCaller&) = delete;

    std::unique_ptr<Gateway::Stub> stub_;
};
