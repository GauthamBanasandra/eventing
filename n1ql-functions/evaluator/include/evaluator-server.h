//
// Created by Gautham Banasandra on 2019-01-18.
//

#ifndef EVALUATOR_SERVICE_H
#define EVALUATOR_SERVICE_H

#include <string>
#include <grpcpp/grpcpp.h>

#include "evaluator.grpc.pb.h"

class EvaluatorServer final : public nftp::Evaluator::Service {
 public:
  grpc::Status Initialize(grpc::ServerContext *context, const nftp::Config *request, nftp::Info *response) override;
  void Run(const std::string &hostname);
};

#endif //EVALUATOR_SERVICE_H
