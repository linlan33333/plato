#pragma once

#include <grpcpp/grpcpp.h>
#include "common/grpc/domain/message/writer/message_writer.grpc.pb.h"

class MessageWriterRpcServiceImpl final : public MessageDomain::MessageWriter::Service
{
public:
    /// @brief 消息域的写服务对外提供的推送消息的接口，理论上这里应该需要按照不同的会话类型采用不同的存储策略，但是
    /// 时间所迫只做聊天IM场景的存储方案
    /// @param context 
    /// @param request 
    /// @param response 
    /// @return 
    grpc::Status PushMessage(grpc::ServerContext* context, const ::MessageDomain::PushMessageRequest* request, ::MessageDomain::PushMessageResponse* response) override;
};