#pragma once

#include "user/rpc/service/impl.h"
#include "common/grpc/domain/user/user.grpc.pb.h"

class UserDomainRpcService
{
public:
    UserDomainRpcService();

    // 启动RPC服务器
    void Start();

private:
    // srpc服务器对象
    grpc::ServerBuilder builder_;

    UserDomainRpcServiceImpl impl_;

    std::unique_ptr<grpc::Server> server_;
};