#include "cli.h"
#include "stdio.h"
#include "timer.h"

#ifndef TIMERS__H__
#define TIMERS__H__

// Uart debugging
static TimerEvent_t HeartBeatTimer;

// Normal operation
static TimerEvent_t PingSlotTimer;
static TimerEvent_t BeaconTimer;
uint16_t BeaconSequenceCount;

// Sequencer as test
static TimerEvent_t SequenceTimer;
uint16_t testMessageCounter = 0;
uint16_t testmessageCount = 0;
uint16_t testIntervalMs = 0;

static void OnBeaconEvent(void* context) {
    BeaconSequenceCount++;
    TimerReset(&BeaconTimer);
}

static void OnHeartbeatEvent(void* context) {
    printf("Beat <3 (b:%d)\n", BeaconSequenceCount);
    TimerReset(&HeartBeatTimer);
}

/**
 * Transmit on a ping slot 
 */
static void OnPingEvent(void* context) {
}

static void OnSequenceEvent(void* context) {
}

void InitTimedTasks() {
    TimerInit(&BeaconTimer, OnBeaconEvent);
    TimerSetValue(&BeaconTimer, 128000);
    TimerStart(&BeaconTimer);

    TimerInit(&HeartBeatTimer, OnHeartbeatEvent);
    TimerSetValue(&HeartBeatTimer, 2500);
    TimerStart(&HeartBeatTimer);

    TimerInit(&PingSlotTimer, OnPingEvent);
    TimerInit(&SequenceTimer, OnSequenceEvent);
    // TimerSetValue(&PingSlotTimer, 2500);
    // TimerStart(&PingSlotTimer);
}

#endif  // TIMERS__H__
