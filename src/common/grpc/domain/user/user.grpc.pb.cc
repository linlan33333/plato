// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: user.proto

#include "common/grpc/domain/user/user.pb.h"
#include "common/grpc/domain/user/user.grpc.pb.h"

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
namespace UserDomain {

static const char* User_method_names[] = {
  "/UserDomain.User/QueryUsers",
  "/UserDomain.User/CreateUsers",
  "/UserDomain.User/UpdateUsers",
};

std::unique_ptr< User::Stub> User::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< User::Stub> stub(new User::Stub(channel, options));
  return stub;
}

User::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_QueryUsers_(User_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CreateUsers_(User_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_UpdateUsers_(User_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status User::Stub::QueryUsers(::grpc::ClientContext* context, const ::UserDomain::QueryUsersRequest& request, ::UserDomain::QueryUsersResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::UserDomain::QueryUsersRequest, ::UserDomain::QueryUsersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_QueryUsers_, context, request, response);
}

void User::Stub::async::QueryUsers(::grpc::ClientContext* context, const ::UserDomain::QueryUsersRequest* request, ::UserDomain::QueryUsersResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::UserDomain::QueryUsersRequest, ::UserDomain::QueryUsersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_QueryUsers_, context, request, response, std::move(f));
}

void User::Stub::async::QueryUsers(::grpc::ClientContext* context, const ::UserDomain::QueryUsersRequest* request, ::UserDomain::QueryUsersResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_QueryUsers_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::UserDomain::QueryUsersResponse>* User::Stub::PrepareAsyncQueryUsersRaw(::grpc::ClientContext* context, const ::UserDomain::QueryUsersRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::UserDomain::QueryUsersResponse, ::UserDomain::QueryUsersRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_QueryUsers_, context, request);
}

::grpc::ClientAsyncResponseReader< ::UserDomain::QueryUsersResponse>* User::Stub::AsyncQueryUsersRaw(::grpc::ClientContext* context, const ::UserDomain::QueryUsersRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncQueryUsersRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status User::Stub::CreateUsers(::grpc::ClientContext* context, const ::UserDomain::CreateUsersRequest& request, ::UserDomain::CreateUsersResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::UserDomain::CreateUsersRequest, ::UserDomain::CreateUsersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CreateUsers_, context, request, response);
}

void User::Stub::async::CreateUsers(::grpc::ClientContext* context, const ::UserDomain::CreateUsersRequest* request, ::UserDomain::CreateUsersResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::UserDomain::CreateUsersRequest, ::UserDomain::CreateUsersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CreateUsers_, context, request, response, std::move(f));
}

void User::Stub::async::CreateUsers(::grpc::ClientContext* context, const ::UserDomain::CreateUsersRequest* request, ::UserDomain::CreateUsersResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CreateUsers_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::UserDomain::CreateUsersResponse>* User::Stub::PrepareAsyncCreateUsersRaw(::grpc::ClientContext* context, const ::UserDomain::CreateUsersRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::UserDomain::CreateUsersResponse, ::UserDomain::CreateUsersRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CreateUsers_, context, request);
}

::grpc::ClientAsyncResponseReader< ::UserDomain::CreateUsersResponse>* User::Stub::AsyncCreateUsersRaw(::grpc::ClientContext* context, const ::UserDomain::CreateUsersRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCreateUsersRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status User::Stub::UpdateUsers(::grpc::ClientContext* context, const ::UserDomain::UpdateUsersRequest& request, ::UserDomain::UpdateUsersResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::UserDomain::UpdateUsersRequest, ::UserDomain::UpdateUsersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_UpdateUsers_, context, request, response);
}

void User::Stub::async::UpdateUsers(::grpc::ClientContext* context, const ::UserDomain::UpdateUsersRequest* request, ::UserDomain::UpdateUsersResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::UserDomain::UpdateUsersRequest, ::UserDomain::UpdateUsersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UpdateUsers_, context, request, response, std::move(f));
}

void User::Stub::async::UpdateUsers(::grpc::ClientContext* context, const ::UserDomain::UpdateUsersRequest* request, ::UserDomain::UpdateUsersResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_UpdateUsers_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::UserDomain::UpdateUsersResponse>* User::Stub::PrepareAsyncUpdateUsersRaw(::grpc::ClientContext* context, const ::UserDomain::UpdateUsersRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::UserDomain::UpdateUsersResponse, ::UserDomain::UpdateUsersRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_UpdateUsers_, context, request);
}

::grpc::ClientAsyncResponseReader< ::UserDomain::UpdateUsersResponse>* User::Stub::AsyncUpdateUsersRaw(::grpc::ClientContext* context, const ::UserDomain::UpdateUsersRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncUpdateUsersRaw(context, request, cq);
  result->StartCall();
  return result;
}

User::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      User_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< User::Service, ::UserDomain::QueryUsersRequest, ::UserDomain::QueryUsersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](User::Service* service,
             ::grpc::ServerContext* ctx,
             const ::UserDomain::QueryUsersRequest* req,
             ::UserDomain::QueryUsersResponse* resp) {
               return service->QueryUsers(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      User_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< User::Service, ::UserDomain::CreateUsersRequest, ::UserDomain::CreateUsersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](User::Service* service,
             ::grpc::ServerContext* ctx,
             const ::UserDomain::CreateUsersRequest* req,
             ::UserDomain::CreateUsersResponse* resp) {
               return service->CreateUsers(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      User_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< User::Service, ::UserDomain::UpdateUsersRequest, ::UserDomain::UpdateUsersResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](User::Service* service,
             ::grpc::ServerContext* ctx,
             const ::UserDomain::UpdateUsersRequest* req,
             ::UserDomain::UpdateUsersResponse* resp) {
               return service->UpdateUsers(ctx, req, resp);
             }, this)));
}

User::Service::~Service() {
}

::grpc::Status User::Service::QueryUsers(::grpc::ServerContext* context, const ::UserDomain::QueryUsersRequest* request, ::UserDomain::QueryUsersResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status User::Service::CreateUsers(::grpc::ServerContext* context, const ::UserDomain::CreateUsersRequest* request, ::UserDomain::CreateUsersResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status User::Service::UpdateUsers(::grpc::ServerContext* context, const ::UserDomain::UpdateUsersRequest* request, ::UserDomain::UpdateUsersResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace UserDomain

