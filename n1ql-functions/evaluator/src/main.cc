//
// Created by Gautham Banasandra on 2019-01-18.
//

#include <iostream>
#include <string>

#include "constants.h"
#include "evaluator-server.h"

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cerr << "Expected at least 4 arguments" << std::endl;
    return 1;
  }
  Constants constants(argv);

  std::string hostname("0.0.0.0:0");
  EvaluatorServer(constants).Run(hostname);
  return 0;
}