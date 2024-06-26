#pragma once

#include <grpcpp/grpcpp.h>
#include "grpc/gateway/gateway.grpc.pb.h"
#include "gateway/netservice.h"

class GatewayRpcServiceImpl final : public Gateway::Service
{
public:
    GatewayRpcServiceImpl(NetService* net_service);

    /// @brief state server发来删除连接信息的信令时处理的逻辑，是RPC方法的具体实现
    /// @param context 
    /// @param request 
    /// @param response 
    /// @return 
    grpc::Status DelConn(grpc::ServerContext* context, const GatewayRequest* request, GatewayResponse *response) override;

    /// @brief state server发来发送消息给用户的信令时处理的逻辑，是RPC方法的具体实现
    /// @param context 
    /// @param request 
    /// @param response 
    /// @return 
    grpc::Status Push(grpc::ServerContext* context, const GatewayRequest* request, GatewayResponse *response) override;

private:
    /// @brief RPC server接收到state server调用的rpc方法后需要操作netservice去把消息发给客户端
	/// 		由于只有RPC server会操作netservice，这里就把它的指针作为成员变量方便调用其接口
	///			感觉这样有点耦合性，后续想想有啥设计模式给它俩分离开
	NetService* net_service_;
};