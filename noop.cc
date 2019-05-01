// Copyright (C) 2017 - 2019, Rory Bradford <rory@dysfunctionalprogramming.com> and contributors
// MIT License

#include <node.h>

namespace notify {

void ready(const v8::FunctionCallbackInfo<v8::Value>& args) {}

void stopping(const v8::FunctionCallbackInfo<v8::Value>& args) {}

void watchdog(const v8::FunctionCallbackInfo<v8::Value>& args) {}

void sendstate(const v8::FunctionCallbackInfo<v8::Value>& args) {}

void interval(const v8::FunctionCallbackInfo<v8::Value>& args) {}

void journal_print(const v8::FunctionCallbackInfo<v8::Value>& args) {}

}  // namespace notify

void Init(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "ready", notify::ready);
  NODE_SET_METHOD(exports, "stopping", notify::stopping);
  NODE_SET_METHOD(exports, "watchdog", notify::watchdog);
  NODE_SET_METHOD(exports, "watchdogInterval", notify::interval);
  NODE_SET_METHOD(exports, "sendState", notify::sendstate);
  NODE_SET_METHOD(exports, "journalPrint", notify::journal_print);
}

NODE_MODULE(addon, Init)

