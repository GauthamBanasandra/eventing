//
// Created by Gautham Banasandra on 2019-01-18.
//

#include <string>

#include "evaluator-server.h"

int main() {
  std::string hostname("0.0.0.0:9090");
  EvaluatorServer().Run(hostname);
  return 0;
}