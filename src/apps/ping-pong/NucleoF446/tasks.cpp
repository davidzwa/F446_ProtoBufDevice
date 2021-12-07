#include "tasks.h"

#include "ProtoWriteBuffer.h"
#include "device_messages.h"
#include "radio_phy.h"
#include "stdio.h"
#include "timer.h"
#include "uart_messages.h"

// Uart debugging
static TimerEvent_t HeartBeatTimer;

// Normal operation
static TimerEvent_t PingSlotTimer;
static TimerEvent_t BeaconTimer;
static TimerEvent_t PeriodicTxTimer;
ProtoWriteBuffer writeTransmitBuffer;
uint16_t beaconSequenceCount;
uint16_t periodicTransmissionMax;
uint16_t periodicCurrentCounter;
uint16_t periodicTxInterval = 1000;

// Sequencer as test
static TimerEvent_t SequenceTimer;
SequenceRequestConfig sequenceRequestConfig;
uint16_t sequenceMessageCount = 0;
bool sequenceTestRunning = false;

static void OnBeaconEvent(void* context) {
    beaconSequenceCount++;
    TimerReset(&BeaconTimer);
}

static void OnHeartbeatEvent(void* context) {
    // printf("Beat <3 (b:%d)\n", BeaconSequenceCount);
    UartSendBoot();
    TimerReset(&HeartBeatTimer);
}

static void OnPeriodicTx(void* context) {
    TransmitCommand<MAX_PAYLOAD_LENGTH> command;
    command.set_IsMulticast(false);
    
    // TODO REPLACE with useful payload
    uint8_t* buffer = (uint8_t*)"ZEDdify me";
    writeTransmitBuffer.clear();
    writeTransmitBuffer.push(buffer, 3);

    command.get_Payload()
        .serialize(writeTransmitBuffer);
    TransmitUnicast(command);

    periodicCurrentCounter++;
    TimerReset(&PeriodicTxTimer);

    if (periodicCurrentCounter > periodicTransmissionMax) {

        TimerStop(&PeriodicTxTimer);
    }
}

void TogglePeriodicTx(uint16_t timerPeriod, uint16_t maxPacketCount) {
    periodicCurrentCounter = 0;

    // Period < 50 Too fast (chance of radio overrun) and nice way to disable the periodic timer
    if (timerPeriod < 50) {
        periodicCurrentCounter = 0;
        TimerStop(&PeriodicTxTimer);
    } else {
        periodicTransmissionMax = maxPacketCount;
        periodicTxInterval = timerPeriod;
        TimerSetValue(&PeriodicTxTimer, periodicTxInterval);
        TimerReset(&PeriodicTxTimer);
    }
}

static void OnPingSlotEvent(void* context) {
}

static void OnSequenceEvent(void* context) {
    sequenceMessageCount++;
}

void SetSequenceRequestConfig(const SequenceRequestConfig& config) {
    if (sequenceTestRunning) return;

    // Check equality - TODO write utility
    // if (!config->get_DeviceId() ) return;

    // Call copy constructor
    sequenceRequestConfig = config;
    sequenceMessageCount = 0;

    TimerSetValue(&SequenceTimer, sequenceRequestConfig.get_Interval());
}

void InitTimedTasks() {
    TimerInit(&BeaconTimer, OnBeaconEvent);
    TimerInit(&HeartBeatTimer, OnHeartbeatEvent);
    TimerInit(&PingSlotTimer, OnPingSlotEvent);
    TimerInit(&SequenceTimer, OnSequenceEvent);
    TimerInit(&PeriodicTxTimer, OnPeriodicTx);

    TimerSetValue(&PeriodicTxTimer, periodicTxInterval);
    TimerSetValue(&BeaconTimer, 128000);
    TimerSetValue(&HeartBeatTimer, 30000);

    TimerStart(&BeaconTimer);
    TimerStart(&HeartBeatTimer);
}
