#include "tasks.h"

#include "ProtoWriteBuffer.h"
#include "config.h"
#include "delay.h"
#include "measurements.h"
#include "radio_phy.h"
#include "stdio.h"
#include "timer.h"

#define MAX_SEQUENCE_NUMBERS 5000
#define DEFAULT_TX_PERIOD 2000
#define HEARTHBEAT_PERIOD 60000

// Uart debugging
static TimerEvent_t heartBeatTimer;

// Normal operation
static TimerEvent_t periodicTxTimer;
ProtoWriteBuffer writeTransmitBuffer;
uint16_t sequenceNumberLimit = MAX_SEQUENCE_NUMBERS;  // Defines the sequencenumber limit
uint16_t periodicCurrentCounter = 0;
uint16_t periodicTxInterval = DEFAULT_TX_PERIOD;

// Sequencer as test
bool standaloneAlwaysSendPeriodically = false;
uint16_t sequenceMessageCount = 0;
bool sequenceTestRunning = false;

bool IsSending() {
    return periodicTxTimer.IsStarted;
}

void StartSending(bool reset) {
    if (reset) {
        TimerReset(&periodicTxTimer);
    }
    else {
        TimerStart(&periodicTxTimer);
    }
}

void StopSending() {
    TimerStop(&periodicTxTimer);
}

bool ApplyPeriodicTxIntervalSafely(uint32_t period) {
    // Period < 50 Too fast (chance of radio overrun) and nice way to disable the periodic timer
    if (period < 50) {
        periodicCurrentCounter = 0;
        StopSending();

        return false;
    } else {
        periodicTxInterval = period;
        TimerSetValue(&periodicTxTimer, periodicTxInterval);
        StartSending(true);

        return true;
    }
}

static void OnHeartbeatEvent(void* context) {
    UartSendBoot();
    StartSending(true);
}

static void OnPeriodicTx(void* context) {
    // We generate a packet as if it came from PC/UART
    LORA_MSG_TEMPLATE command;
    command.set_IsMulticast(false);

    // TODO REPLACE with useful payload
    uint8_t* test_message = (uint8_t*)"ZEDdify me";
    auto payload = command.mutable_Payload();
    payload.set(test_message, sizeof(test_message));
    command.set_CorrelationCode(periodicCurrentCounter);

    TransmitLoRaMessage(command);
    UartDebug("PeriodTX", periodicCurrentCounter, 8);
    periodicCurrentCounter++;

    if (periodicCurrentCounter > sequenceNumberLimit) {
        if (standaloneAlwaysSendPeriodically) {
            // We start again with new counter
            periodicCurrentCounter = 0;
            StartSending(true);
        } else {
            // We will send the data once
            // RequestStreamMeasurements();
            StopSending();
        }
    } else {
        StartSending(true);
    }
}

/**
 * Send periodically indefinitely
 * */
void ApplyAlwaysSendPeriodically(DeviceConfiguration& configuration) {
    standaloneAlwaysSendPeriodically = configuration.get_EnableAlwaysSend();
    auto alwaysSendPeriod = configuration.get_AlwaysSendPeriod();
    auto limitedSendCount = configuration.get_LimitedSendCount();

    if (standaloneAlwaysSendPeriodically) {
        standaloneAlwaysSendPeriodically = true;
        periodicCurrentCounter = 0;
        sequenceNumberLimit = limitedSendCount; // Sequence looparound 

        ApplyPeriodicTxIntervalSafely(alwaysSendPeriod);
    } else {
        standaloneAlwaysSendPeriodically = false;
        sequenceNumberLimit = limitedSendCount;
        periodicCurrentCounter = 0;

        if (limitedSendCount == 0) {
            StopSending();
        }
        else {
            ApplyPeriodicTxIntervalSafely(alwaysSendPeriod);
        }
    }
}

void InitTimedTasks() {
    TimerInit(&heartBeatTimer, OnHeartbeatEvent);
    TimerInit(&periodicTxTimer, OnPeriodicTx);

    TimerSetValue(&heartBeatTimer, HEARTHBEAT_PERIOD);
    TimerSetValue(&periodicTxTimer, periodicTxInterval);

    standaloneAlwaysSendPeriodically = false;
    TimerStart(&heartBeatTimer);
}
