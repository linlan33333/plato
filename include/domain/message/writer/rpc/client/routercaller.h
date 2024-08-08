#pragma once

#include "common/grpc/router/router.grpc.pb.h"

class RouterCaller {
public:
    static RouterCaller& Get();

    void PushMessage(uint64_t user_id, std::string& data);

    void FanoutMessage(std::string& data);

private:
    RouterCaller();
    RouterCaller(const RouterCaller&) = delete;
    RouterCaller& operator=(const RouterCaller&) = delete;

    // router server的stub对象
    std::unique_ptr<Router::Router::Stub> stub_;
};