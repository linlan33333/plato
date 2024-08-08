#pragma once

#include "common/grpc/router/router.grpc.pb.h"
#include <grpcpp/grpcpp.h>

class RouterRpcServiceImpl final : public Router::Router::Service 
{
public:
    /// @brief 供接入层调用，当长连接网关有新客户端接入时调用
    /// @param context 
    /// @param request 
    /// @param response 
    /// @return 
    grpc::Status AddRecord(grpc::ServerContext* context, const Router::AddRecordRequest* request, Router::AddRecordResponse *response) override;

    /// @brief 供以后分布式化改造后的push server调用，用来查询某个用户的所有在线设备的连接信息
    /// @param context 
    /// @param request 
    /// @param response 
    /// @return 
    grpc::Status QueryRecord(grpc::ServerContext* context, const Router::QueryRecordRequest* request, Router::QueryRecordResponse *response) override;

    /// @brief 删除记录，当用户某台设备断开与网关的连接时调用，删除该设备连接信息
    /// @param context 
    /// @param request 
    /// @param response 
    /// @return 
    grpc::Status DelRecord(grpc::ServerContext* context, const Router::DelRecordRequest* request, Router::DelRecordResponse *response) override;

    /// @brief 发送下行消息给用户，可能是信令，反正就是message.proto中的MsgCmd
    /// @param context 
    /// @param request 
    /// @param response 
    /// @return 
    grpc::Status PushMessage(grpc::ServerContext* context, const Router::PushMessageRequest* request, Router::PushMessageResponse *response) override;

    /// @brief 广播消息给所有用户
    /// @param context
    /// @param request
    /// @param response
    /// @return
    grpc::Status FanoutMessage(grpc::ServerContext* context, const Router::FanoutMessageRequest* request, Router::FanoutMessageResponse *response) override;
};