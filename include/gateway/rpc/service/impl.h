#pragma once

#include "srpc/gateway/gateway.pb.h"
#include "srpc/gateway/gateway.srpc.h"
#include "gateway/netservice.h"

using namespace srpc;

class GatewayRpcServiceImpl : public Gateway::Service
{
public:
	GatewayRpcServiceImpl(NetService* net_service);

	/// @brief state server发来删除连接信息的信令时处理的逻辑，是RPC方法的具体实现
	/// @param request 
	/// @param response 
	/// @param ctx 
	void DelConn(GatewayRequest *request, GatewayResponse *response, srpc::RPCContext *ctx) override;

	/// @brief state server发来发送消息给用户的信令时处理的逻辑，是RPC方法的具体实现
	/// @param request 
	/// @param response 
	/// @param ctx 
	void Push(GatewayRequest *request, GatewayResponse *response, srpc::RPCContext *ctx) override;

private:

	/// @brief RPC server接收到state server调用的rpc方法后需要操作netservice去把消息发给客户端
	/// 		由于只有RPC server会操作netservice，这里就把它的指针作为成员变量方便调用其接口
	///			感觉这样有点耦合性，后续想想有啥设计模式给它俩分离开
	NetService* net_service_;
};