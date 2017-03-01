#include <node.h>
#include <systemd/sd-daemon.h>

#define READY "READY=1"

using namespace v8;

void Notify(const FunctionCallbackInfo<Value>& args) {
  sd_notify(0, READY);
}

void Init(Local<Object> exports, Local<Object> module) {
  NODE_SET_METHOD(module, "exports", Notify);
}

NODE_MODULE(addon, Init)
