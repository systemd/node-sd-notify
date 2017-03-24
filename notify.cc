// Copyright (C) 2017, Rory Bradford <roryrjb@protonmail.com>
// MIT License

#include <node.h>
#include <systemd/sd-daemon.h>

#define READY "READY=1"

namespace notify {

void ready(const v8::FunctionCallbackInfo<v8::Value>& args) {
  sd_notify(0, READY);
}

}

void Init(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "ready", notify::ready);
}

NODE_MODULE(addon, Init)


