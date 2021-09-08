#include "tx.h"

#include "rtc-board.h"

TimerEvent_t timerHandle;

uint16_t testMessageCounter = 0;
uint16_t testmessageCount = 0;
uint16_t testIntervalMs = 0;

uint16_t msgSize = BUFFER_SIZE;
uint8_t buffer[BUFFER_SIZE];

bool testRunning = false;

void TxBuffer(int16_t dataSize) {
    if (dataSize < 0) {
        dataSize = BUFFER_SIZE;
    }

    // Print msg in hex
    printf("[TX]");
    for (int i = 0; i < dataSize; i++) {
        printf("0x%02X ", buffer[i]);
    }
    printf("\n\r");

    // Goodbye msg
    Radio.Send(buffer, dataSize);
    DelayMs(1);
}

void TxPing() {
    // Send the next PING frame
    buffer[0] = '\0';
    buffer[1] = 'I';
    buffer[2] = 'N';
    buffer[3] = 'G';

    TxBuffer(4);
}

void TxDeviceId() {
    DeviceId_t deviceId = GetDeviceId();
    // Send the next PING frame
    buffer[0] = (deviceId.id0 >> 24) & 0xff;
    buffer[1] = (deviceId.id0 >> 16) & 0xff;
    buffer[2] = (deviceId.id0 >> 8) & 0xff;
    buffer[3] = deviceId.id0 & 0xff;

    TxBuffer(msgSize);
}

void TxPong() {
    // Send the next PING frame
    buffer[0] = '\0';
    buffer[1] = 'O';
    buffer[2] = 'N';
    buffer[3] = 'G';

    TxBuffer(4);
}

void TxSpreadingFactor(uint8_t unicodeValue) {
    // Send the next SF frame
    buffer[0] = 'S';
    buffer[1] = unicodeValue;

    TxBuffer(2);
}

void TxNewRFSettings(uint8_t *serialBuf, uint8_t bufSize){
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


void TxTestProcess(){

    if(TestRunning){
        if(testMessageCounter++ < testmessageCount){
            printf("[tx] SequenceTest %d from %d\n\r", testMessageCounter, testmessageCount);
            TxTestMessage();
            DelayMs(testIntervalMs);
        } else {
            testRunning = false;
            printf("[tx] SequenceTest Done\n\r");
        }
    }
}

void TxStartSequenceTest(uint16_t messageCount, uint16_t intervalMs) {
    printf("[tx] TxStartSequenceTest\n\r");

    // if(TestRunning){
    //     printf("[tx] test already running %d msg left\n\r", testMessageLeft);
    //     return;
    // }

    testMessageCounter = 0;
    testIntervalMs = intervalMs;
    testmessageCount = messageCount;

    testRunning = true;
}
