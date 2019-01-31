//
// Created by Gautham Banasandra on 2019-01-30.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

struct Constants {
  explicit Constants(char *argv[])
      : executable_path(argv[0]), notification_port(argv[1]),
        evaluator_id(argv[2]),
        num_threads(static_cast<std::size_t>(std::stoi(argv[3]))) {}

  std::string executable_path;
  std::string notification_port;
  std::string evaluator_id;
  std::size_t num_threads;
};

#endif // CONSTANTS_H
