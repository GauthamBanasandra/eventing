//
// Created by Gautham Banasandra on 2019-01-30.
//

#include <libplatform/libplatform.h>

#include "evaluator.h"
#include "utils.h"

Info RuntimeBundle::AddFunction(const Function &function) {
  v8::Locker locker(isolate);
  v8::Isolate::Scope isolate_scope(isolate);
  v8::HandleScope handle_scope(isolate);
  auto context = v8::Context::New(isolate);
  v8::Context::Scope context_scope(context);

  v8::Local<v8::String> source;
  if (!TO_LOCAL(v8::String::NewFromUtf8(isolate, function.code.c_str(),
                                        v8::NewStringType::kNormal),
                &source)) {
    return {true, "Unable to create source string"};
  }

  v8::Local<v8::Script> script;
  if (!TO_LOCAL(v8::Script::Compile(context, source), &script)) {
    return {true, "Unable to compile source"};
  }

  v8::Local<v8::Value> result;
  v8::TryCatch try_catch(isolate);
  if (!TO_LOCAL(script->Run(context), &result)) {
    if (try_catch.HasCaught()) {
      return {true, "Syntax error"};
    }
    return {true, "Unable to run script"};
  }
  contexts[function.id].Reset(isolate, context);
  return {false};
}

RuntimeBundle::~RuntimeBundle() {
  for (auto &context : contexts) {
    context.second.Reset();
  }
  isolate->Dispose();
}

Evaluator::Evaluator(const Constants &constants,
                     NotificationClient &notification_client)
    : const_(constants), notification_client_(notification_client) {
  v8::V8::InitializeICUDefaultLocation("");
  platform_ = v8::platform::CreateDefaultPlatform();
  v8::V8::InitializePlatform(platform_);
  v8::V8::Initialize();

  isolate_params_.array_buffer_allocator =
      v8::ArrayBuffer::Allocator::NewDefaultAllocator();

  isolate_ = v8::Isolate::New(isolate_params_);
  for (const auto &thread_id : const_.threads_ids) {
    runtimes_[thread_id].isolate = v8::Isolate::New(isolate_params_);
  }
  notification_client_.Log("Initialized isolate");
}

Evaluator::~Evaluator() {
  for (auto &runtime : runtimes_) {
    runtime.second.isolate->Dispose();
  }

  v8::V8::Dispose();
  v8::V8::ShutdownPlatform();
  delete platform_;
  delete isolate_params_.array_buffer_allocator;
}

Info Evaluator::AddFunction(const Function &function) {
  auto info = Compile(function.code);
  if (info.is_fatal) {
    return info;
  }

  for (auto &runtime : runtimes_) {
    info = runtime.second.AddFunction(function);
    if (info.is_fatal) {
      return info;
    }
  }
  return {false};
}

Info Evaluator::Evaluate(const EvaluateRequest &request) {
  notification_client_.Log("Received Evaluate");
  auto find_it = runtimes_.find(request.thread_id);
  if (find_it == runtimes_.end()) {
    return {true, "No runtime found for " + request.thread_id};
  }

  auto &runtime = find_it->second;
  auto isolate = runtime.isolate;
  v8::Locker locker(isolate);
  v8::Isolate::Scope isolate_scope(isolate);
  v8::HandleScope handle_scope(isolate);
  auto context = runtime.contexts[request.function_id].Get(isolate);
  v8::Context::Scope context_scope(context);

  auto global = context->Global();
  v8::Local<v8::Value> function_val;
  if (!TO_LOCAL(
      global->Get(context, v8::String::NewFromUtf8(
          isolate, request.function_name.c_str())),
      &function_val)) {
    return {true, "Unable to get function from global"};
  }

  auto function = function_val.As<v8::Function>();
  if (function->IsNullOrUndefined()) {
    return {true, "Function " + request.function_name + " not found"};
  }

  v8::Local<v8::Value> result;
  v8::TryCatch try_catch(isolate);
  if (!TO_LOCAL(function->Call(context, global, 0, nullptr), &result)) {
    if (try_catch.HasCaught()) {
      return {true, "exception thrown"};
    }
    return {true, "Unable to call function"};
  }

  v8::String::Utf8Value result_utf8(result);
  return {false, *result_utf8};
}

Info Evaluator::Compile(const std::string &code) {
  v8::Locker locker(isolate_);
  v8::Isolate::Scope isolate_scope(isolate_);
  v8::HandleScope handle_scope(isolate_);
  auto context = v8::Context::New(isolate_);
  v8::Context::Scope context_scope(context);

  v8::Local<v8::String> source;
  if (!TO_LOCAL(v8::String::NewFromUtf8(isolate_, code.c_str(),
                                        v8::NewStringType::kNormal),
                &source)) {
    return {true, "Unable to create source string"};
  }

  v8::Local<v8::Script> script;
  if (!TO_LOCAL(v8::Script::Compile(context, source), &script)) {
    return {true, "Unable to compile source"};
  }

  v8::Local<v8::Value> result;
  v8::TryCatch try_catch(isolate_);
  if (!TO_LOCAL(script->Run(context), &result)) {
    if (try_catch.HasCaught()) {
      return {true, "Syntax error"};
    }
    return {true, "Unable to run script"};
  }
  return {false};
}
