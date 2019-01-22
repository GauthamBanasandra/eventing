//
// Created by Gautham Banasandra on 2019-01-18.
//

#include <string>
#include <iostream>

#include "evaluator-server.h"

int main(int argc, char *argv[]) {
  std::cout << argc << std::endl;
  for (int i = 0; i < argc; ++i) {
    std::cout << argv[i] << std::endl;
  }

  std::string hostname("0.0.0.0:0");
  EvaluatorServer().Run(hostname);
  return 0;
}