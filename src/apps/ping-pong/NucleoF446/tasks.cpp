#include "tasks.h"

#include "ProtoWriteBuffer.h"
#include "config.h"
#include "delay.h"
#include "measurements.h"
#include "radio_phy.h"
#include "radio_config.h"
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

bool IsSending() {
    return periodicTxTimer.IsStarted;
}

void StartPeriodicTransmit(bool reset) {
    if (reset) {
        TimerReset(&periodicTxTimer);
    }
    else {
        TimerStart(&periodicTxTimer);
    }
}

void StopPeriodicTransmit() {
    TimerStop(&periodicTxTimer);
}

bool ApplyPeriodicTxIntervalSafely(uint32_t period) {
    // Period < 50 Too fast (chance of radio overrun) and nice way to disable the periodic timer
    if (period < 50) {
        periodicCurrentCounter = 0;
        StopPeriodicTransmit();

        return false;
    } else {
        periodicTxInterval = period;
        TimerSetValue(&periodicTxTimer, periodicTxInterval);
        StartPeriodicTransmit(true);

        return true;
    }
}

static void OnHeartbeatEvent(void* context) {
    UartSendBoot();
    TimerStart(&heartBeatTimer);
}

static void OnPeriodicTx(void* context) {
    // We generate a packet as if it came from PC/UART
    LORA_MSG_TEMPLATE command;
    command.set_IsMulticast(true);

    // TODO REPLACE with useful payload
    uint8_t* test_message = (uint8_t*)"ZEDdify me";
    auto payload = command.mutable_Payload();
    payload.set(test_message, sizeof(test_message));
    command.set_CorrelationCode(periodicCurrentCounter);

    auto dummyConfig = command.mutable_dummyConfig();
    dummyConfig.set_TxPower(GetTxPower());
    dummyConfig.set_TxRxBandwidth(GetTxBandwidth());
    dummyConfig.set_TxRxDataRate(GetTxDataRate());

    TransmitLoRaMessage(command);
    UartDebug("PeriodTX", periodicCurrentCounter, 8);
    periodicCurrentCounter++;
    
    if (periodicCurrentCounter >= sequenceNumberLimit) {
        if (standaloneAlwaysSendPeriodically) {
            // We start again with new counter
            periodicCurrentCounter = 0;
            StartPeriodicTransmit(true);
        } else {
            // We will send the data once
            // RequestStreamMeasurements();
            StopPeriodicTransmit();
        }
    } else {
        StartPeriodicTransmit(true);
    }
}

/**
 * Send periodically indefinitely
 * */
void ApplyAlwaysSendPeriodically(DeviceConfiguration& configuration) {   
    // Patch/Apply the config
    auto sequenceConfig = configuration.get_sequenceConfiguration();  
    standaloneAlwaysSendPeriodically = sequenceConfig.EnableAlwaysSend();
    auto alwaysSendPeriod = sequenceConfig.get_AlwaysSendPeriod();
    auto limitedSendCount = sequenceConfig.get_LimitedSendCount();

    if (standaloneAlwaysSendPeriodically) {
        // Rare case of infinite transmitting
        standaloneAlwaysSendPeriodically = true;
        periodicCurrentCounter = 0;
        sequenceNumberLimit = limitedSendCount; // Sequence looparound 

        ApplyPeriodicTxIntervalSafely(alwaysSendPeriod);
    } else {
        // Common case - limited sequence
        standaloneAlwaysSendPeriodically = false;
        sequenceNumberLimit = limitedSendCount;
        periodicCurrentCounter = 0;

        if ((uint32_t)limitedSendCount == 0U) {
            StopPeriodicTransmit();
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
