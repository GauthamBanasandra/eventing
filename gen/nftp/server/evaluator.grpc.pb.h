// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: evaluator.proto
#ifndef GRPC_evaluator_2eproto__INCLUDED
#define GRPC_evaluator_2eproto__INCLUDED

#include "evaluator.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace nftp {

class Notification final {
 public:
  static constexpr char const* service_full_name() {
    return "nftp.Notification";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status NotifyPort(::grpc::ClientContext* context, const ::nftp::Port& request, ::nftp::Void* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>> AsyncNotifyPort(::grpc::ClientContext* context, const ::nftp::Port& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>>(AsyncNotifyPortRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>> PrepareAsyncNotifyPort(::grpc::ClientContext* context, const ::nftp::Port& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>>(PrepareAsyncNotifyPortRaw(context, request, cq));
    }
    virtual ::grpc::Status Logger(::grpc::ClientContext* context, const ::nftp::Log& request, ::nftp::Void* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>> AsyncLogger(::grpc::ClientContext* context, const ::nftp::Log& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>>(AsyncLoggerRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>> PrepareAsyncLogger(::grpc::ClientContext* context, const ::nftp::Log& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>>(PrepareAsyncLoggerRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>* AsyncNotifyPortRaw(::grpc::ClientContext* context, const ::nftp::Port& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>* PrepareAsyncNotifyPortRaw(::grpc::ClientContext* context, const ::nftp::Port& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>* AsyncLoggerRaw(::grpc::ClientContext* context, const ::nftp::Log& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Void>* PrepareAsyncLoggerRaw(::grpc::ClientContext* context, const ::nftp::Log& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status NotifyPort(::grpc::ClientContext* context, const ::nftp::Port& request, ::nftp::Void* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Void>> AsyncNotifyPort(::grpc::ClientContext* context, const ::nftp::Port& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Void>>(AsyncNotifyPortRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Void>> PrepareAsyncNotifyPort(::grpc::ClientContext* context, const ::nftp::Port& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Void>>(PrepareAsyncNotifyPortRaw(context, request, cq));
    }
    ::grpc::Status Logger(::grpc::ClientContext* context, const ::nftp::Log& request, ::nftp::Void* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Void>> AsyncLogger(::grpc::ClientContext* context, const ::nftp::Log& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Void>>(AsyncLoggerRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Void>> PrepareAsyncLogger(::grpc::ClientContext* context, const ::nftp::Log& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Void>>(PrepareAsyncLoggerRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::nftp::Void>* AsyncNotifyPortRaw(::grpc::ClientContext* context, const ::nftp::Port& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::nftp::Void>* PrepareAsyncNotifyPortRaw(::grpc::ClientContext* context, const ::nftp::Port& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::nftp::Void>* AsyncLoggerRaw(::grpc::ClientContext* context, const ::nftp::Log& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::nftp::Void>* PrepareAsyncLoggerRaw(::grpc::ClientContext* context, const ::nftp::Log& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_NotifyPort_;
    const ::grpc::internal::RpcMethod rpcmethod_Logger_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status NotifyPort(::grpc::ServerContext* context, const ::nftp::Port* request, ::nftp::Void* response);
    virtual ::grpc::Status Logger(::grpc::ServerContext* context, const ::nftp::Log* request, ::nftp::Void* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_NotifyPort : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_NotifyPort() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_NotifyPort() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status NotifyPort(::grpc::ServerContext* context, const ::nftp::Port* request, ::nftp::Void* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestNotifyPort(::grpc::ServerContext* context, ::nftp::Port* request, ::grpc::ServerAsyncResponseWriter< ::nftp::Void>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_Logger : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Logger() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_Logger() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Logger(::grpc::ServerContext* context, const ::nftp::Log* request, ::nftp::Void* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestLogger(::grpc::ServerContext* context, ::nftp::Log* request, ::grpc::ServerAsyncResponseWriter< ::nftp::Void>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_NotifyPort<WithAsyncMethod_Logger<Service > > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_NotifyPort : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_NotifyPort() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_NotifyPort() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status NotifyPort(::grpc::ServerContext* context, const ::nftp::Port* request, ::nftp::Void* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_Logger : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Logger() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_Logger() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Logger(::grpc::ServerContext* context, const ::nftp::Log* request, ::nftp::Void* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_NotifyPort : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_NotifyPort() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::nftp::Port, ::nftp::Void>(std::bind(&WithStreamedUnaryMethod_NotifyPort<BaseClass>::StreamedNotifyPort, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_NotifyPort() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status NotifyPort(::grpc::ServerContext* context, const ::nftp::Port* request, ::nftp::Void* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedNotifyPort(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::nftp::Port,::nftp::Void>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Logger : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Logger() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler< ::nftp::Log, ::nftp::Void>(std::bind(&WithStreamedUnaryMethod_Logger<BaseClass>::StreamedLogger, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Logger() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Logger(::grpc::ServerContext* context, const ::nftp::Log* request, ::nftp::Void* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedLogger(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::nftp::Log,::nftp::Void>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_NotifyPort<WithStreamedUnaryMethod_Logger<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_NotifyPort<WithStreamedUnaryMethod_Logger<Service > > StreamedService;
};

class Evaluator final {
 public:
  static constexpr char const* service_full_name() {
    return "nftp.Evaluator";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status Initialize(::grpc::ClientContext* context, const ::nftp::Config& request, ::nftp::Info* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>> AsyncInitialize(::grpc::ClientContext* context, const ::nftp::Config& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>>(AsyncInitializeRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>> PrepareAsyncInitialize(::grpc::ClientContext* context, const ::nftp::Config& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>>(PrepareAsyncInitializeRaw(context, request, cq));
    }
    virtual ::grpc::Status AddFunction(::grpc::ClientContext* context, const ::nftp::Function& request, ::nftp::Info* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>> AsyncAddFunction(::grpc::ClientContext* context, const ::nftp::Function& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>>(AsyncAddFunctionRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>> PrepareAsyncAddFunction(::grpc::ClientContext* context, const ::nftp::Function& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>>(PrepareAsyncAddFunctionRaw(context, request, cq));
    }
    virtual ::grpc::Status Evaluate(::grpc::ClientContext* context, const ::nftp::Params& request, ::nftp::Info* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>> AsyncEvaluate(::grpc::ClientContext* context, const ::nftp::Params& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>>(AsyncEvaluateRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>> PrepareAsyncEvaluate(::grpc::ClientContext* context, const ::nftp::Params& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>>(PrepareAsyncEvaluateRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>* AsyncInitializeRaw(::grpc::ClientContext* context, const ::nftp::Config& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>* PrepareAsyncInitializeRaw(::grpc::ClientContext* context, const ::nftp::Config& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>* AsyncAddFunctionRaw(::grpc::ClientContext* context, const ::nftp::Function& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>* PrepareAsyncAddFunctionRaw(::grpc::ClientContext* context, const ::nftp::Function& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>* AsyncEvaluateRaw(::grpc::ClientContext* context, const ::nftp::Params& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::nftp::Info>* PrepareAsyncEvaluateRaw(::grpc::ClientContext* context, const ::nftp::Params& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status Initialize(::grpc::ClientContext* context, const ::nftp::Config& request, ::nftp::Info* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>> AsyncInitialize(::grpc::ClientContext* context, const ::nftp::Config& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>>(AsyncInitializeRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>> PrepareAsyncInitialize(::grpc::ClientContext* context, const ::nftp::Config& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>>(PrepareAsyncInitializeRaw(context, request, cq));
    }
    ::grpc::Status AddFunction(::grpc::ClientContext* context, const ::nftp::Function& request, ::nftp::Info* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>> AsyncAddFunction(::grpc::ClientContext* context, const ::nftp::Function& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>>(AsyncAddFunctionRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>> PrepareAsyncAddFunction(::grpc::ClientContext* context, const ::nftp::Function& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>>(PrepareAsyncAddFunctionRaw(context, request, cq));
    }
    ::grpc::Status Evaluate(::grpc::ClientContext* context, const ::nftp::Params& request, ::nftp::Info* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>> AsyncEvaluate(::grpc::ClientContext* context, const ::nftp::Params& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>>(AsyncEvaluateRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>> PrepareAsyncEvaluate(::grpc::ClientContext* context, const ::nftp::Params& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::nftp::Info>>(PrepareAsyncEvaluateRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::nftp::Info>* AsyncInitializeRaw(::grpc::ClientContext* context, const ::nftp::Config& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::nftp::Info>* PrepareAsyncInitializeRaw(::grpc::ClientContext* context, const ::nftp::Config& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::nftp::Info>* AsyncAddFunctionRaw(::grpc::ClientContext* context, const ::nftp::Function& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::nftp::Info>* PrepareAsyncAddFunctionRaw(::grpc::ClientContext* context, const ::nftp::Function& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::nftp::Info>* AsyncEvaluateRaw(::grpc::ClientContext* context, const ::nftp::Params& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::nftp::Info>* PrepareAsyncEvaluateRaw(::grpc::ClientContext* context, const ::nftp::Params& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Initialize_;
    const ::grpc::internal::RpcMethod rpcmethod_AddFunction_;
    const ::grpc::internal::RpcMethod rpcmethod_Evaluate_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status Initialize(::grpc::ServerContext* context, const ::nftp::Config* request, ::nftp::Info* response);
    virtual ::grpc::Status AddFunction(::grpc::ServerContext* context, const ::nftp::Function* request, ::nftp::Info* response);
    virtual ::grpc::Status Evaluate(::grpc::ServerContext* context, const ::nftp::Params* request, ::nftp::Info* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_Initialize : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Initialize() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Initialize() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Initialize(::grpc::ServerContext* context, const ::nftp::Config* request, ::nftp::Info* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestInitialize(::grpc::ServerContext* context, ::nftp::Config* request, ::grpc::ServerAsyncResponseWriter< ::nftp::Info>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_AddFunction : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_AddFunction() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_AddFunction() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AddFunction(::grpc::ServerContext* context, const ::nftp::Function* request, ::nftp::Info* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestAddFunction(::grpc::ServerContext* context, ::nftp::Function* request, ::grpc::ServerAsyncResponseWriter< ::nftp::Info>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_Evaluate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Evaluate() {
      ::grpc::Service::MarkMethodAsync(2);
    }
    ~WithAsyncMethod_Evaluate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Evaluate(::grpc::ServerContext* context, const ::nftp::Params* request, ::nftp::Info* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestEvaluate(::grpc::ServerContext* context, ::nftp::Params* request, ::grpc::ServerAsyncResponseWriter< ::nftp::Info>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Initialize<WithAsyncMethod_AddFunction<WithAsyncMethod_Evaluate<Service > > > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_Initialize : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Initialize() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Initialize() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Initialize(::grpc::ServerContext* context, const ::nftp::Config* request, ::nftp::Info* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_AddFunction : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_AddFunction() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_AddFunction() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status AddFunction(::grpc::ServerContext* context, const ::nftp::Function* request, ::nftp::Info* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_Evaluate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Evaluate() {
      ::grpc::Service::MarkMethodGeneric(2);
    }
    ~WithGenericMethod_Evaluate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Evaluate(::grpc::ServerContext* context, const ::nftp::Params* request, ::nftp::Info* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Initialize : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Initialize() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::nftp::Config, ::nftp::Info>(std::bind(&WithStreamedUnaryMethod_Initialize<BaseClass>::StreamedInitialize, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Initialize() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Initialize(::grpc::ServerContext* context, const ::nftp::Config* request, ::nftp::Info* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedInitialize(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::nftp::Config,::nftp::Info>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_AddFunction : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_AddFunction() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler< ::nftp::Function, ::nftp::Info>(std::bind(&WithStreamedUnaryMethod_AddFunction<BaseClass>::StreamedAddFunction, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_AddFunction() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status AddFunction(::grpc::ServerContext* context, const ::nftp::Function* request, ::nftp::Info* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedAddFunction(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::nftp::Function,::nftp::Info>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Evaluate : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Evaluate() {
      ::grpc::Service::MarkMethodStreamed(2,
        new ::grpc::internal::StreamedUnaryHandler< ::nftp::Params, ::nftp::Info>(std::bind(&WithStreamedUnaryMethod_Evaluate<BaseClass>::StreamedEvaluate, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Evaluate() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Evaluate(::grpc::ServerContext* context, const ::nftp::Params* request, ::nftp::Info* response) final override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedEvaluate(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::nftp::Params,::nftp::Info>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_Initialize<WithStreamedUnaryMethod_AddFunction<WithStreamedUnaryMethod_Evaluate<Service > > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_Initialize<WithStreamedUnaryMethod_AddFunction<WithStreamedUnaryMethod_Evaluate<Service > > > StreamedService;
};

}  // namespace nftp


#endif  // GRPC_evaluator_2eproto__INCLUDED
