//
// Created by Gautham Banasandra on 2019-01-30.
//

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <string>
#include <unordered_map>
#include <vector>
#include <v8.h>
#include <thread>

#include "constants.h"
#include "function.h"
#include "info.h"
#include "notification-client.h"

using ThreadID = std::string;

struct RuntimeBundle{
  ~RuntimeBundle();

  Info AddFunction(const Function &function);

  v8::Isolate *isolate;
  std::unordered_map<FunctionID, v8::Persistent<v8::Context>> contexts;
};

class Evaluator {
public:
  explicit Evaluator(const Constants &constants, NotificationClient &notification_client);
  virtual ~Evaluator();

  Info AddFunction(const Function &function);
  Info Evaluate(const Params& params);

private:
  Info Compile(const std::string &code);

  const Constants &const_;
  NotificationClient &notification_client_;
  v8::Platform *platform_;
  v8::Isolate *isolate_;
  v8::Isolate::CreateParams isolate_params_;
  std::unordered_map<ThreadID, RuntimeBundle> runtimes_;
};

#endif // EVALUATOR_H
