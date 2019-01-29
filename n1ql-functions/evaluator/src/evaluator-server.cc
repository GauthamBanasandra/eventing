//
// Created by Gautham Banasandra on 2019-01-18.
//

#include <iostream>
#include <memory>
#include <string>

#include "evaluator-server.h"

EvaluatorServer::EvaluatorServer(const std::string &notification_port) {
  auto channel = grpc::CreateChannel("127.0.0.1:" + notification_port,
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

void EvaluatorServer::Run(const std::string &hostname, const std::string &evaluator_id) {
  grpc::ServerBuilder builder;
  int selected_port = 0;
  builder.AddListeningPort(hostname, grpc::InsecureServerCredentials(),
                           &selected_port);
  builder.RegisterService(this);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << selected_port << std::endl;

  grpc::ClientContext context;
  nftp::Port port;
  port.set_evaluatorid(evaluator_id);
  port.set_port(static_cast<google::protobuf::uint32>(selected_port));

  nftp::Void void_resp;
  auto status = notification_client_->NotifyPort(&context, port, &void_resp);
  std::cout << "status : " << status.ok() << std::endl;
  server->Wait();
}
