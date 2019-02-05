//
// Created by Gautham Banasandra on 2019-01-31.
//

#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>

#include "evaluator.pb.h"

using FunctionID = std::string;

struct Function {
  Function(const nftp::Function *function)
      : id(function->id()), code(function->code()) {}

  FunctionID id;
  std::string code;
};

struct EvaluateRequest {
  EvaluateRequest(const nftp::EvaluateRequest *request)
      : function_id(request->functionid()),
        function_name(request->functionname()), thread_id(request->threadid()) {
  }

  std::string function_id;
  std::string function_name;
  std::string thread_id;
};

#endif // FUNCTION_H
