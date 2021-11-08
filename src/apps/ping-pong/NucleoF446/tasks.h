#include "timer.h"
#include "cli.h"

#ifndef TIMERS__H__
#define TIMERS__H__

static TimerEvent_t Led1Timer;
static void OnLed1TimerEvent(void* context) {
    UartSendBoot();
}

void InitTimedTasks() {
    TimerInit(&Led1Timer, OnLed1TimerEvent);
    TimerSetValue(&Led1Timer, 1000);
}

#endif  // TIMERS__H__
