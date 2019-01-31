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

struct RuntimeBundle{
  ~RuntimeBundle();

  v8::Isolate *isolate;
  v8::Persistent<v8::Context> context;
};

class Evaluator {
public:
  explicit Evaluator(const Constants &constants, NotificationClient &notification_client);
  virtual ~Evaluator();

  Info AddFunction(const Function &function);

private:
  const Constants &const_;
  NotificationClient &notification_client_;
  v8::Platform *platform_;
  v8::Isolate *isolate_;
  v8::Isolate::CreateParams isolate_params_;
  std::unordered_map<std::string, RuntimeBundle> runtime_;
};

#endif // EVALUATOR_H
