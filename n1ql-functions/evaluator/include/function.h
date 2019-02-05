//
// Created by Gautham Banasandra on 2019-01-31.
//

#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>

#include "evaluator.pb.h"

using FunctionID = std::string;

struct Function {
  Function(const nftp::Function *function) : id(function->id()), code(function->code()) {}

  FunctionID id;
  std::string code;
};

struct Params {
  Params(const nftp::Params *params) : function_id(params->functionid()), function_name(params->functionname()) {}

  std::string function_id;
  std::string function_name;
};

#endif // FUNCTION_H
