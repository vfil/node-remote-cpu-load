#include <node.h>
#include <iostream>
#include <mach/mach_host.h>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Number;
using v8::Value;

static unsigned long _previousTotalTicks = 0;
static unsigned long _previousIdleTicks = 0;

/**
should be called at regular intervals as algorithm is based on cpu statistics between consecutive calls.
First call result should be ignored.
*/
float GetCPULoad()
{
    host_cpu_load_info_data_t cpu_info;
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
    if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpu_info, &count) == KERN_SUCCESS)
    {
        unsigned long totalTicks = 0;
        for(int i=0; i<CPU_STATE_MAX; i++) totalTicks += cpu_info.cpu_ticks[i];

        unsigned long idleTicks = cpu_info.cpu_ticks[CPU_STATE_IDLE];

        unsigned long deltaTotalTicks = totalTicks - _previousTotalTicks;
        unsigned long deltaIdleTicks  = idleTicks - _previousIdleTicks;

        _previousTotalTicks = totalTicks;
        _previousIdleTicks  = idleTicks;

        float result = 1.0f-((deltaTotalTicks > 0) ? ((float)deltaIdleTicks)/deltaTotalTicks : 0);

        return result;
    }

    else return -1.0f;
}

//TODO is it worth to turn it in async function???
void Method(const FunctionCallbackInfo<Value>& args) {

  float load = GetCPULoad();

  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(Number::New(isolate, load));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "retrieve", Method);
}

NODE_MODULE(cpuload, init)
