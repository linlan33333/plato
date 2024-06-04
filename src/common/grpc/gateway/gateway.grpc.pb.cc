// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: gateway.proto

#include "grpc/gateway/gateway.pb.h"
#include "grpc/gateway/gateway.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>

static const char* Gateway_method_names[] = {
  "/Gateway/DelConn",
  "/Gateway/Push",
};

std::unique_ptr< Gateway::Stub> Gateway::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Gateway::Stub> stub(new Gateway::Stub(channel, options));
  return stub;
}

Gateway::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_DelConn_(Gateway_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Push_(Gateway_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Gateway::Stub::DelConn(::grpc::ClientContext* context, const ::GatewayRequest& request, ::GatewayResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::GatewayRequest, ::GatewayResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_DelConn_, context, request, response);
}

void Gateway::Stub::async::DelConn(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::GatewayRequest, ::GatewayResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DelConn_, context, request, response, std::move(f));
}

void Gateway::Stub::async::DelConn(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_DelConn_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::GatewayResponse>* Gateway::Stub::PrepareAsyncDelConnRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::GatewayResponse, ::GatewayRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_DelConn_, context, request);
}

::grpc::ClientAsyncResponseReader< ::GatewayResponse>* Gateway::Stub::AsyncDelConnRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncDelConnRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Gateway::Stub::Push(::grpc::ClientContext* context, const ::GatewayRequest& request, ::GatewayResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::GatewayRequest, ::GatewayResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Push_, context, request, response);
}

void Gateway::Stub::async::Push(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::GatewayRequest, ::GatewayResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Push_, context, request, response, std::move(f));
}

void Gateway::Stub::async::Push(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Push_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::GatewayResponse>* Gateway::Stub::PrepareAsyncPushRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::GatewayResponse, ::GatewayRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Push_, context, request);
}

::grpc::ClientAsyncResponseReader< ::GatewayResponse>* Gateway::Stub::AsyncPushRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncPushRaw(context, request, cq);
  result->StartCall();
  return result;
}

Gateway::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Gateway_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Gateway::Service, ::GatewayRequest, ::GatewayResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Gateway::Service* service,
             ::grpc::ServerContext* ctx,
             const ::GatewayRequest* req,
             ::GatewayResponse* resp) {
               return service->DelConn(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Gateway_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Gateway::Service, ::GatewayRequest, ::GatewayResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](Gateway::Service* service,
             ::grpc::ServerContext* ctx,
             const ::GatewayRequest* req,
             ::GatewayResponse* resp) {
               return service->Push(ctx, req, resp);
             }, this)));
}

Gateway::Service::~Service() {
}

::grpc::Status Gateway::Service::DelConn(::grpc::ServerContext* context, const ::GatewayRequest* request, ::GatewayResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Gateway::Service::Push(::grpc::ServerContext* context, const ::GatewayRequest* request, ::GatewayResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

