#include "timer.h"
#include "cli.h"

#ifndef TIMERS__H__
#define TIMERS__H__

static TimerEvent_t Led1Timer;
static void OnBeaconEvent(void* context) {
    

    // TimerSetValue(&Led1Timer, 1000);
    // TimerStart(&Led1Timer);
    TimerReset(&Led1Timer);
}

void InitTimedTasks() {
    TimerInit(&Led1Timer, OnBeaconEvent);
    TimerSetValue(&Led1Timer, 128000);
    TimerStart(&Led1Timer);
}

#endif  // TIMERS__H__
