//
// Created by Gautham Banasandra on 2019-01-30.
//

#include <libplatform/libplatform.h>

#include "evaluator.h"
#include "utils.h"

RuntimeBundle::~RuntimeBundle() {
  context.Reset();
}

Evaluator::Evaluator(const Constants &constants, NotificationClient &notification_client)
    : const_(constants), notification_client_(notification_client) {
  v8::V8::InitializeICUDefaultLocation("");
  platform_ = v8::platform::CreateDefaultPlatform();
  v8::V8::InitializePlatform(platform_);
  v8::V8::Initialize();

  isolate_params_.array_buffer_allocator =
      v8::ArrayBuffer::Allocator::NewDefaultAllocator();
  isolate_ = v8::Isolate::New(isolate_params_);
  notification_client_.Log("Initialized isolate");
}

Evaluator::~Evaluator() {
  for (auto &runtime : runtime_) {
    runtime.second.context.Reset();
    runtime.second.isolate->Dispose();
  }

  v8::V8::Dispose();
  v8::V8::ShutdownPlatform();
  delete platform_;
  delete isolate_params_.array_buffer_allocator;
}

Info Evaluator::AddFunction(const Function &function) {
  v8::Locker locker(isolate_);
  notification_client_.Log("Adding Function");
  v8::Isolate::Scope isolate_scope(isolate_);
  v8::HandleScope handle_scope(isolate_);
  auto context = v8::Context::New(isolate_);
  v8::Context::Scope context_scope(context);

  v8::Local<v8::String> source;
  if (!TO_LOCAL(v8::String::NewFromUtf8(isolate_, function.code.c_str(),
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

  v8::String::Utf8Value utf8_result(result);
  std::cout << *utf8_result << std::endl;
  runtime_[function.id].isolate = isolate_;
  runtime_[function.id].context.Reset(isolate_, context);
  return {false, *utf8_result};
}

Info Evaluator::Evaluate(const Params &params) {
  notification_client_.Log("Received Evaluate");
  v8::Locker locker(isolate_);
  v8::Isolate::Scope isolate_scope(isolate_);
  v8::HandleScope handle_scope(isolate_);
  auto context = runtime_[params.function_id].context.Get(isolate_);
  v8::Context::Scope context_scope(context);

  auto global = context->Global();
  v8::Local<v8::Value> function_val;
  if (!TO_LOCAL(global->Get(context, v8::String::NewFromUtf8(isolate_, params.function_name.c_str())), &function_val)) {
    return {true, "Unable to get function from global"};
  }

  auto function = function_val.As<v8::Function>();
  v8::Local<v8::Value> result;
  if (!TO_LOCAL(function->Call(context, global, 0, nullptr), &result)) {
    return {true, "Unable to call function"};
  }

  v8::String::Utf8Value result_utf8(result);
  return {false, *result_utf8};
}
