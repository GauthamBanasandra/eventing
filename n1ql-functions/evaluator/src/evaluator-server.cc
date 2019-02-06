//
// Created by Gautham Banasandra on 2019-01-18.
//

#include <iostream>
#include <memory>
#include <string>

#include "evaluator-server.h"

EvaluatorServer::EvaluatorServer(const Constants &constants,
                                 Evaluator &evaluator)
    : evaluator_(evaluator), const_(constants) {
  auto channel = grpc::CreateChannel("127.0.0.1:" + const_.notification_port,
                                     grpc::InsecureChannelCredentials());
  notification_client_ = nftp::Notification::NewStub(channel);
}

grpc::Status EvaluatorServer::Initialize(grpc::ServerContext *context,
                                         const nftp::Config *request,
                                         nftp::Info *response) {
  std::cout << "Got request : Initialize" << std::endl;
  std::cout << "WorkersPerNode : " << request->workerspernode() << std::endl;
  std::cout << "ThreadsPerWorker : " << request->threadsperworker()
            << std::endl;
  response->set_isfatal(false);
  response->set_message("All is well");
  return grpc::Status::OK;
}

void EvaluatorServer::Run(const std::string &hostname) {
  grpc::ServerBuilder builder;
  int selected_port = 0;
  builder.AddListeningPort(hostname, grpc::InsecureServerCredentials(),
                           &selected_port);
  builder.RegisterService(this);
  server_ = builder.BuildAndStart();
  std::cout << "Server listening on " << selected_port << std::endl;

  grpc::ClientContext context;
  nftp::Port port;
  port.set_evaluatorid(const_.evaluator_id);
  port.set_port(static_cast<google::protobuf::uint32>(selected_port));

  nftp::Void void_resp;
  auto status = notification_client_->NotifyPort(&context, port, &void_resp);
  std::cout << "status : " << status.ok() << std::endl;
  server_->Wait();
}

grpc::Status EvaluatorServer::AddFunction(grpc::ServerContext *context,
                                          const nftp::Function *request,
                                          nftp::Info *response) {
  auto info = evaluator_.AddFunction({request});
  response->set_isfatal(info.is_fatal);
  response->set_message(info.msg);
  return grpc::Status::OK;
}

grpc::Status EvaluatorServer::Evaluate(grpc::ServerContext *context,
                                       const nftp::EvaluateRequest *request,
                                       nftp::Info *response) {
  auto info = evaluator_.Evaluate({request});
  response->set_isfatal(info.is_fatal);
  response->set_message(info.msg);
  return grpc::Status::OK;
}

grpc::Status EvaluatorServer::Stop(grpc::ServerContext *context,
                                   const nftp::Void *request,
                                   nftp::Void *response) {
  server_->Shutdown();
  return grpc::Status::OK;
}
