#include "cli.h"
#include "device_messages.h"
#include "lora_device_messages.h"

#ifndef TIMERS__H__
#define TIMERS__H__

void SetSequenceRequestConfig(const SequenceRequestConfig& config);
void ApplyAlwaysSendPeriodically(bool alwaysSend, uint32_t period);
void TogglePeriodicTx(uint16_t timerPeriod, uint16_t maxPacketCount);
void InitTimedTasks();

#endif  // TIMERS__H__
