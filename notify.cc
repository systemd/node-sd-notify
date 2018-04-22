// Copyright (C) 2017 - 2018, Rory Bradford <roryrjb@gmail.com> and contributors
// MIT License

#include <node.h>
#include <systemd/sd-daemon.h>

#define READY "READY=1"
#define STOPPING "STOPPING=1"
#define WATCHDOG "WATCHDOG=1"

namespace notify {

const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "STATUS=conversion failed";
}

void ready(const v8::FunctionCallbackInfo<v8::Value>& args) {
  int pid = args[0]->NumberValue();
  sd_pid_notify(pid, 0, READY);
}

void stopping(const v8::FunctionCallbackInfo<v8::Value>& args) {
  int pid = args[0]->NumberValue();
  sd_pid_notify(pid, 0, STOPPING);
}

void watchdog(const v8::FunctionCallbackInfo<v8::Value>& args) {
  sd_notify(0, WATCHDOG);
}

void sendstate(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::String::Utf8Value str(args[0]);
  const char *state = ToCString(str);
  sd_notify(0, state);
}

void interval(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  uint64_t interval;
  int res = sd_watchdog_enabled(0, &interval);

  if (res > 0) {
      args.GetReturnValue().Set(v8::Number::New(isolate, interval / 1000));
  } else {
      args.GetReturnValue().Set(v8::Number::New(isolate, 0));
  }
}

}  // namespace notify

void Init(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "ready", notify::ready);
  NODE_SET_METHOD(exports, "stopping", notify::stopping);
  NODE_SET_METHOD(exports, "watchdog", notify::watchdog);
  NODE_SET_METHOD(exports, "watchdogInterval", notify::interval);
  NODE_SET_METHOD(exports, "sendState", notify::sendstate);
}

NODE_MODULE(addon, Init)

