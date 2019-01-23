// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: evaluator.proto

#include "evaluator.pb.h"
#include "evaluator.grpc.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace nftp {

static const char* Notification_method_names[] = {
  "/nftp.Notification/NotifyPort",
};

std::unique_ptr< Notification::Stub> Notification::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Notification::Stub> stub(new Notification::Stub(channel));
  return stub;
}

Notification::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_NotifyPort_(Notification_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Notification::Stub::NotifyPort(::grpc::ClientContext* context, const ::nftp::Port& request, ::nftp::Void* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_NotifyPort_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::nftp::Void>* Notification::Stub::AsyncNotifyPortRaw(::grpc::ClientContext* context, const ::nftp::Port& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::nftp::Void>::Create(channel_.get(), cq, rpcmethod_NotifyPort_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::nftp::Void>* Notification::Stub::PrepareAsyncNotifyPortRaw(::grpc::ClientContext* context, const ::nftp::Port& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::nftp::Void>::Create(channel_.get(), cq, rpcmethod_NotifyPort_, context, request, false);
}

Notification::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Notification_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Notification::Service, ::nftp::Port, ::nftp::Void>(
          std::mem_fn(&Notification::Service::NotifyPort), this)));
}

Notification::Service::~Service() {
}

::grpc::Status Notification::Service::NotifyPort(::grpc::ServerContext* context, const ::nftp::Port* request, ::nftp::Void* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* Evaluator_method_names[] = {
  "/nftp.Evaluator/Initialize",
};

std::unique_ptr< Evaluator::Stub> Evaluator::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Evaluator::Stub> stub(new Evaluator::Stub(channel));
  return stub;
}

Evaluator::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Initialize_(Evaluator_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Evaluator::Stub::Initialize(::grpc::ClientContext* context, const ::nftp::Config& request, ::nftp::Info* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Initialize_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::nftp::Info>* Evaluator::Stub::AsyncInitializeRaw(::grpc::ClientContext* context, const ::nftp::Config& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::nftp::Info>::Create(channel_.get(), cq, rpcmethod_Initialize_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::nftp::Info>* Evaluator::Stub::PrepareAsyncInitializeRaw(::grpc::ClientContext* context, const ::nftp::Config& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::nftp::Info>::Create(channel_.get(), cq, rpcmethod_Initialize_, context, request, false);
}

Evaluator::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Evaluator_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Evaluator::Service, ::nftp::Config, ::nftp::Info>(
          std::mem_fn(&Evaluator::Service::Initialize), this)));
}

Evaluator::Service::~Service() {
}

::grpc::Status Evaluator::Service::Initialize(::grpc::ServerContext* context, const ::nftp::Config* request, ::nftp::Info* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace nftp
