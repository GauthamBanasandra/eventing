//
// Created by Gautham Banasandra on 2019-01-18.
//

#ifndef EVALUATOR_SERVICE_H
#define EVALUATOR_SERVICE_H

#include <grpc++/grpc++.h>
#include <memory>
#include <string>

#include "constants.h"
#include "evaluator.h"
#include "evaluator.grpc.pb.h"

class EvaluatorServer final : public nftp::Evaluator::Service {
 public:
  explicit EvaluatorServer(const Constants &constants, Evaluator &evaluator);

  grpc::Status Initialize(grpc::ServerContext *context,
                          const nftp::Config *request,
                          nftp::Info *response) override;
  grpc::Status AddFunction(grpc::ServerContext *context,
                           const nftp::Function *request,
                           nftp::Info *response) override;
  void Run(const std::string &hostname);

 private:
  Evaluator &evaluator_;
  const Constants &const_;
  std::unique_ptr<nftp::Notification::Stub> notification_client_;
};

#endif // EVALUATOR_SERVICE_H
