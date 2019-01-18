//
// Created by Gautham Banasandra on 2019-01-18.
//

#include <string>
#include <iostream>
#include <memory>

#include "evaluator-server.h"

grpc::Status EvaluatorServer::Initialize(grpc::ServerContext *context,
                                          const nftp::Config *request,
                                          nftp::Info *response) {
  std::cout << "Got request : Initialize" << std::endl;
  std::cout << "WorkersPerNode : " << request->workerspernode() << std::endl;
  std::cout << "ThreadsPerWorker : " << request->threadsperworker() << std::endl;
  response->set_isfatal(false);
  response->set_message("All is well");
  return grpc::Status::OK;
}

void EvaluatorServer::Run(const std::string &hostname) {
  grpc::ServerBuilder builder;
  builder.AddListeningPort(hostname, grpc::InsecureServerCredentials());
  builder.RegisterService(this);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << hostname << std::endl;
  server->Wait();
}
