//
// Created by Gautham Banasandra on 2019-01-30.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>
#include <string>

struct Constants {
  explicit Constants(char *argv[]);

  std::string executable_path;
  std::string notification_port;
  std::string evaluator_id;
  std::size_t num_threads;
  std::vector<std::string> threads_ids;

 private:
  std::size_t i_arg{0};
};

#endif // CONSTANTS_H
