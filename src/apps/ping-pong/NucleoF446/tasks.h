#include "cli.h"
#include "lora_device_messages.h"

#ifndef TIMERS__H__
#define TIMERS__H__

bool IsSending();
void StopPeriodicTransmit();
void ApplyAlwaysSendPeriodically(DeviceConfiguration& configuration);
void InitTimedTasks();

#endif  // TIMERS__H__
