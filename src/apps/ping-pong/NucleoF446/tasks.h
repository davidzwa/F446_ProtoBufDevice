#include "timer.h"
#include "cli.h"

#ifndef TIMERS__H__
#define TIMERS__H__

static TimerEvent_t BeaconTimer;
uint16_t BeaconSequence;
static void OnBeaconEvent(void* context) {
    BeaconSequence++;
    printf("Beacon sent %d\n", BeaconSequence);
    TimerReset(&BeaconTimer);
}

void InitTimedTasks() {
    TimerInit(&BeaconTimer, OnBeaconEvent);
    TimerSetValue(&BeaconTimer, 128000);
    TimerStart(&BeaconTimer);
}

#endif  // TIMERS__H__
