//
// Created by Gautham Banasandra on 2019-01-18.
//

#include <iostream>
#include <string>

#include "evaluator-server.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Expected at least 3 arguments" << std::endl;
    return 1;
  }

  std::string notification_port(argv[1]);
  std::string evaluator_id(argv[2]);

  std::string hostname("0.0.0.0:0");
  EvaluatorServer(notification_port).Run(hostname, evaluator_id);
  return 0;
}