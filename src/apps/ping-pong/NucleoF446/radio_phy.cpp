#include "radio_phy.h"


uint16_t msgSize = BUFFER_SIZE;
uint8_t buffer[BUFFER_SIZE];

bool isExecutingCommand = false;
bool testRunning = false;
int8_t lastRssiValue = 0;
int8_t lastSnrValue = 0;

/*!
 * \brief Radio interupts
 */
void OnTxDone(void);
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
void OnTxTimeout(void);
void OnRxTimeout(void);
void OnRxError(void);

/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

void InitRadioPhy() {
    // Radio initialization
    RadioEvents.TxDone = OnTxDone;
    RadioEvents.RxDone = OnRxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxTimeout = OnRxTimeout;
    RadioEvents.RxError = OnRxError;

    Radio.Init(&RadioEvents);
    Radio.SetChannel(RF_FREQUENCY);

#if defined(USE_MODEM_LORA)

    Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                      LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, LORA_IQ_INVERSION_ON, 3000);

    Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                      LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                      LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                      0, true, 0, 0, LORA_IQ_INVERSION_ON, true);

    Radio.SetMaxPayloadLength(MODEM_LORA, BUFFER_SIZE);

#elif defined(USE_MODEM_FSK)

    Radio.SetTxConfig(MODEM_FSK, TX_OUTPUT_POWER, FSK_FDEV, 0,
                      FSK_DATARATE, 0,
                      FSK_PREAMBLE_LENGTH, FSK_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, 0, 3000);

    Radio.SetRxConfig(MODEM_FSK, FSK_BANDWIDTH, FSK_DATARATE,
                      0, FSK_AFC_BANDWIDTH, FSK_PREAMBLE_LENGTH,
                      0, FSK_FIX_LENGTH_PAYLOAD_ON, 0, true,
                      0, 0, false, true);

    Radio.SetMaxPayloadLength(MODEM_FSK, BUFFER_SIZE);

#else
#error "Please define a frequency band in the compiler options."
#endif
}

void OnTxDone(void) {
    ApplyConfigIfPending();

    if (!isExecutingCommand) {
        Radio.Rx(RX_TIMEOUT_VALUE);
    } else {
        Radio.Sleep();
    }
}

void OnTxTimeout(void) {
    ApplyConfigIfPending();

    if (!isExecutingCommand) {
        Radio.Rx(RX_TIMEOUT_VALUE);
    } else {
        Radio.Sleep();
    }
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
    msgSize = size;
    memcpy(buffer, payload, msgSize);
    lastRssiValue = rssi;
    lastSnrValue = snr;

    printf("[Main]");
    for (int i = 0; i < msgSize; i++) {
        printf("0x%02X ", buffer[i]);
    }
    printf("\n[Main] MsgSize: %d RssiValue: %d SnrValue: %d\n", msgSize, rssi, snr);

    parseMsg(buffer, msgSize);

    // Listen for next radio packet
    Radio.Rx(RX_TIMEOUT_VALUE);
}

void OnRxTimeout(void) {
    // printf("[Main] OnRxTimeout\n");
    Radio.Rx(RX_TIMEOUT_VALUE);
}

void OnRxError(void) {
    printf("[Main] error\n");
    Radio.Rx(RX_TIMEOUT_VALUE);
}

void ProcessSequenceCommand(uint8_t *buffer) {
    uint16_t messageCount = (buffer[1] << 8) + buffer[2];
    uint16_t intervalMs = (buffer[3] << 8) + buffer[4];
    uint32_t deviceId = (buffer[5] << 24) + (buffer[6] << 16) + (buffer[7] << 8) + buffer[8];

    // DeviceId currentDeviceId = GetDeviceId();

    // // deviceId = 0 => multicast
    // if (deviceId && currentDeviceId.get_Id0() != deviceId) {
    //     printf("[rx] Device id0 %lu was not equal to %lu! Command ignored.\n\r", currentDeviceId.id0, deviceId);
    // } else {
    //     if (intervalMs < 150) {
    //         printf("[rx] Device ID recognized, but intervalMS %d was too low (<150). Ignoring command", intervalMs);
    //     } else {
    //         // testMessageLeft = messageCount;
    //         // testmessageCount = messageCount;
    //         // testintervalMs = intervalMs;

    //         printf("[rx] Device id %lu recognized. Test Packets: %d, interval: %d ms\n\r", deviceId, messageCount, intervalMs);

    //         TxStartSequenceTest(messageCount, intervalMs);
    //     }
    // }
}

void parseMsg(uint8_t *RfBuffer, uint8_t msgSize) {
    switch (RfBuffer[0]) {
        // Set Spreading factor
        case 'S':
            // if (msgSize > 1) {
            //     ProcessSpreadingFactorMessage(RfBuffer[1], true);
            // }
            break;

        // Execute sequence cmd
        case 'T':
            if (msgSize > 8) {
                ProcessSequenceCommand(RfBuffer);
            }
            break;

        // parse RF config packet
        case 'F':
            // SetNewRFSettings((uint8_t *) RfBuffer, msgSize);
            break;

        default:
            break;
    }
}

void TxBuffer(int16_t dataSize) {
    if (dataSize < 0) {
        dataSize = BUFFER_SIZE;
    }

    // Goodbye msg
    Radio.Send(buffer, dataSize);
    DelayMs(1);
}

void TxSpreadingFactor(uint8_t unicodeValue) {
    // Send the next SF frame
    buffer[0] = 'S';
    buffer[1] = unicodeValue;

    TxBuffer(2);
}

void TxNewRFSettings(uint8_t *serialBuf, uint8_t bufSize) {
    memcpy(buffer, serialBuf, bufSize);
    TxBuffer(bufSize);
}

void TxSequenceCommand(uint8_t *serialBuf, uint8_t bufSize) {
    if (bufSize > 8) {
        memcpy(buffer, serialBuf, 9);
    } else {
        uint16_t messageCount = 5;
        uint16_t intervalMs = 500;
        uint32_t deviceId = 0x00;

        printf("[tx] DefaultSequenceCMD: messageCount %d, intervalMs %d, deviceId %lu\n\r", messageCount, intervalMs, deviceId);

        buffer[0] = 'T';
        buffer[1] = (messageCount >> 8) & 0xff;
        buffer[2] = messageCount & 0xff;
        buffer[3] = (intervalMs >> 8) & 0xff;
        buffer[4] = intervalMs & 0xff;
        buffer[5] = (deviceId >> 24) & 0xff;
        buffer[6] = (deviceId >> 16) & 0xff;
        buffer[7] = (deviceId >> 8) & 0xff;
        buffer[8] = deviceId & 0xff;

        for (int i = 9; i < msgSize; i++) {
            buffer[i] = i % 2;
        }
    }

    TxBuffer(msgSize);
}

void TxTestProcess() {
    if (testRunning) {
        if (testMessageCounter++ < testmessageCount) {
            printf("[tx] SequenceTest %d from %d\n\r", testMessageCounter, testmessageCount);
            TxDeviceId();
            DelayMs(testIntervalMs);
        } else {
            testRunning = false;
            printf("[tx] SequenceTest Done\n\r");
        }
    }
}

void TxStartSequenceTest(uint16_t messageCount, uint16_t intervalMs) {
    printf("[tx] TxStartSequenceTest\n\r");

    // if(testRunning){
    //     printf("[tx] test already running %d msg left\n\r", testMessageLeft);
    //     return;
    // }

    testMessageCounter = 0;
    testIntervalMs = intervalMs;
    testmessageCount = messageCount;

    testRunning = true;
}

void ProcessSpreadingFactorMessage(uint8_t spreadingFactor, bool broadcastLoRa) {
    if (IsValidSpreadingFactor(spreadingFactor)) {
        if (broadcastLoRa) {
            TxSpreadingFactor(spreadingFactor);
            printf("[CLI] Broadcasting SF %d\n\r", spreadingFactor);

            pendingConfigChange = true;
            UpdateRadioSpreadingFactor(spreadingFactor, false);
        } else {
            UpdateRadioSpreadingFactor(spreadingFactor, true);
        }

        printf("[CLI] Set Radio SF '%d' \n\r", spreadingFactor);
    } else {
        printf("[CLI] SF not 7,8,9,0,1,2(=12) skipped: '%c'\n\r", spreadingFactor);
    }
}
