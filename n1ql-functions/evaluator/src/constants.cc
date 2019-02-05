//
// Created by Gautham Banasandra on 2019-02-05.
//

#include <algorithm>

#include "constants.h"

Constants::Constants(char *argv[]) {
  executable_path = argv[i_arg++];
  notification_port = argv[i_arg++];
  evaluator_id = argv[i_arg++];
  num_threads = static_cast<std::size_t>(std::stoi(argv[i_arg++]));

  threads_ids.resize(num_threads);
  std::generate(threads_ids.begin(), threads_ids.end(), [this, argv]() -> std::string {
    return argv[i_arg++];
  });
}
