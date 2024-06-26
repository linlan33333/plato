// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: gateway.proto
#ifndef GRPC_gateway_2eproto__INCLUDED
#define GRPC_gateway_2eproto__INCLUDED

#include "gateway.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

// 网关机的rpc server定义
// cd gateway/rpc 下执行protoc去编译
class Gateway final {
 public:
  static constexpr char const* service_full_name() {
    return "Gateway";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status DelConn(::grpc::ClientContext* context, const ::GatewayRequest& request, ::GatewayResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>> AsyncDelConn(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>>(AsyncDelConnRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>> PrepareAsyncDelConn(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>>(PrepareAsyncDelConnRaw(context, request, cq));
    }
    virtual ::grpc::Status Push(::grpc::ClientContext* context, const ::GatewayRequest& request, ::GatewayResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>> AsyncPush(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>>(AsyncPushRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>> PrepareAsyncPush(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>>(PrepareAsyncPushRaw(context, request, cq));
    }
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void DelConn(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void DelConn(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      virtual void Push(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, std::function<void(::grpc::Status)>) = 0;
      virtual void Push(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, ::grpc::ClientUnaryReactor* reactor) = 0;
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>* AsyncDelConnRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>* PrepareAsyncDelConnRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>* AsyncPushRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::GatewayResponse>* PrepareAsyncPushRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status DelConn(::grpc::ClientContext* context, const ::GatewayRequest& request, ::GatewayResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GatewayResponse>> AsyncDelConn(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GatewayResponse>>(AsyncDelConnRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GatewayResponse>> PrepareAsyncDelConn(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GatewayResponse>>(PrepareAsyncDelConnRaw(context, request, cq));
    }
    ::grpc::Status Push(::grpc::ClientContext* context, const ::GatewayRequest& request, ::GatewayResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GatewayResponse>> AsyncPush(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GatewayResponse>>(AsyncPushRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GatewayResponse>> PrepareAsyncPush(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::GatewayResponse>>(PrepareAsyncPushRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void DelConn(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, std::function<void(::grpc::Status)>) override;
      void DelConn(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
      void Push(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, std::function<void(::grpc::Status)>) override;
      void Push(::grpc::ClientContext* context, const ::GatewayRequest* request, ::GatewayResponse* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::GatewayResponse>* AsyncDelConnRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::GatewayResponse>* PrepareAsyncDelConnRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::GatewayResponse>* AsyncPushRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::GatewayResponse>* PrepareAsyncPushRaw(::grpc::ClientContext* context, const ::GatewayRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_DelConn_;
    const ::grpc::internal::RpcMethod rpcmethod_Push_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status DelConn(::grpc::ServerContext* context, const ::GatewayRequest* request, ::GatewayResponse* response);
    virtual ::grpc::Status Push(::grpc::ServerContext* context, const ::GatewayRequest* request, ::GatewayResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_DelConn : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_DelConn() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_DelConn() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DelConn(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestDelConn(::grpc::ServerContext* context, ::GatewayRequest* request, ::grpc::ServerAsyncResponseWriter< ::GatewayResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_Push : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_Push() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_Push() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Push(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPush(::grpc::ServerContext* context, ::GatewayRequest* request, ::grpc::ServerAsyncResponseWriter< ::GatewayResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_DelConn<WithAsyncMethod_Push<Service > > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_DelConn : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_DelConn() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::GatewayRequest, ::GatewayResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::GatewayRequest* request, ::GatewayResponse* response) { return this->DelConn(context, request, response); }));}
    void SetMessageAllocatorFor_DelConn(
        ::grpc::MessageAllocator< ::GatewayRequest, ::GatewayResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::GatewayRequest, ::GatewayResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_DelConn() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DelConn(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* DelConn(
      ::grpc::CallbackServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithCallbackMethod_Push : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_Push() {
      ::grpc::Service::MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::GatewayRequest, ::GatewayResponse>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::GatewayRequest* request, ::GatewayResponse* response) { return this->Push(context, request, response); }));}
    void SetMessageAllocatorFor_Push(
        ::grpc::MessageAllocator< ::GatewayRequest, ::GatewayResponse>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::GatewayRequest, ::GatewayResponse>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_Push() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Push(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* Push(
      ::grpc::CallbackServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_DelConn<WithCallbackMethod_Push<Service > > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_DelConn : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_DelConn() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_DelConn() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DelConn(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_Push : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_Push() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_Push() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Push(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_DelConn : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_DelConn() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_DelConn() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DelConn(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestDelConn(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_Push : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_Push() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_Push() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Push(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPush(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_DelConn : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_DelConn() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->DelConn(context, request, response); }));
    }
    ~WithRawCallbackMethod_DelConn() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status DelConn(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* DelConn(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_Push : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_Push() {
      ::grpc::Service::MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->Push(context, request, response); }));
    }
    ~WithRawCallbackMethod_Push() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Push(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* Push(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_DelConn : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_DelConn() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::GatewayRequest, ::GatewayResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::GatewayRequest, ::GatewayResponse>* streamer) {
                       return this->StreamedDelConn(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_DelConn() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status DelConn(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedDelConn(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::GatewayRequest,::GatewayResponse>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Push : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_Push() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::GatewayRequest, ::GatewayResponse>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::GatewayRequest, ::GatewayResponse>* streamer) {
                       return this->StreamedPush(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_Push() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Push(::grpc::ServerContext* /*context*/, const ::GatewayRequest* /*request*/, ::GatewayResponse* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedPush(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::GatewayRequest,::GatewayResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_DelConn<WithStreamedUnaryMethod_Push<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_DelConn<WithStreamedUnaryMethod_Push<Service > > StreamedService;
};


#endif  // GRPC_gateway_2eproto__INCLUDED
