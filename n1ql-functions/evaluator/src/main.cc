//
// Created by Gautham Banasandra on 2019-01-18.
//

#include <iostream>
#include <string>

#include "constants.h"
#include "evaluator-server.h"
#include "evaluator.h"
#include "notification-client.h"

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cerr << "Expected at least 4 arguments" << std::endl;
    return 1;
  }
  Constants constants(argv);

  NotificationClient client(constants);
  Evaluator evaluator(constants, client);
  std::string hostname("0.0.0.0:0");
  EvaluatorServer(constants, evaluator).Run(hostname);
  return 0;
}