#include "cli.h"
#include "lora_device_messages.h"

#ifndef TIMERS__H__
#define TIMERS__H__

void ApplyAlwaysSendPeriodically(bool alwaysSend, uint32_t period, uint32_t maxPacketCount);
void InitTimedTasks();

#endif  // TIMERS__H__
