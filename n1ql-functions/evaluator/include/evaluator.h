//
// Created by Gautham Banasandra on 2019-01-30.
//

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <string>
#include <thread>
#include <unordered_map>
#include <v8.h>
#include <vector>

#include "constants.h"
#include "library.h"
#include "info.h"
#include "notification-client.h"

using ThreadID = std::string;

struct RuntimeBundle {
  ~RuntimeBundle();

  Info AddLibrary(const Library &library);

  v8::Isolate *isolate;
  std::unordered_map<LibraryID, v8::Persistent<v8::Context>> contexts;
};

class Evaluator {
public:
  explicit Evaluator(const Constants &constants,
                     NotificationClient &notification_client);
  virtual ~Evaluator();

  Info AddLibrary(const Library &library);
  Info Evaluate(const EvaluateRequest &request);

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
