//
// Created by Gautham Banasandra on 2019-01-18.
//

#include <iostream>
#include <string>

#include "evaluator-server.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Expected at least 2 arguments" << std::endl;
    return 1;
  }

  std::string hostname("0.0.0.0:0");
  EvaluatorServer(argv[1]).Run(hostname);
  return 0;
}