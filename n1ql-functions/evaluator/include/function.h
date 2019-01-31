//
// Created by Gautham Banasandra on 2019-01-31.
//

#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>

#include "evaluator.pb.h"

struct Function {
  Function() = default;
  Function(const nftp::Function *function) : id(function->id()), code(function->code()) {}

  std::string id;
  std::string code;
};

#endif // FUNCTION_H
