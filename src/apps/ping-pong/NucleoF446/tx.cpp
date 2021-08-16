#include "tx.h"

#include "delay.h"
#include "stdio.h"

uint16_t bufferSize = BUFFER_SIZE;
uint8_t buffer[BUFFER_SIZE];

void TxBuffer(int16_t dataSize) {
    if(dataSize < 0){
        dataSize = BUFFER_SIZE;
    }

    // Print msg in hex
    printf("[TX]");
    for (int i = 0; i < dataSize; i++) {
         printf("0x%02X ", buffer[i] );
    }
    printf("\n\r");

    // Goodbye msg
    Radio.Send(buffer, BUFFER_SIZE);
    DelayMs(1);
}

void TxPing() {
    // Send the next PING frame
    buffer[0] = 'P';
    buffer[1] = 'I';
    buffer[2] = 'N';
    buffer[3] = 'G';

    // We fill the buffer with numbers for the payload
    for (int i = 4; i < bufferSize; i++) {
        buffer[i] = i - 4;
    }

    TxBuffer(4);
}

void TxPong() {
    // Send the next PING frame
    buffer[0] = 'P';
    buffer[1] = 'O';
    buffer[2] = 'N';
    buffer[3] = 'G';
    // We fill the buffer with numbers for the payload
    for (int i = 4; i < bufferSize; i++) {
        buffer[i] = i - 4;
    }

    TxBuffer(4);
}

void TxSpreadingFactor(uint8_t unicodeValue) {
    // Send the next SF frame
    buffer[0] = 'S';
    buffer[1] = unicodeValue;
    // We fill the buffer with zeroes for the payload
    for (int i = 2; i < bufferSize; i++) {
        buffer[i] = 0;
    }

    TxBuffer(2);
}

void TxSequenceCommand(SequenceCommand_t cmd) {
    int i = 0;
    // Send the next sequence TX command
    buffer[i++] = 'T';  // 0x54
    buffer[i++] = cmd.messageCount & 0xff;
    buffer[i++] = (cmd.messageCount >> 8) & 0xff;
    buffer[i++] = cmd.intervalMs & 0xff;
    buffer[i++] = (cmd.intervalMs >> 8) & 0xff;
    buffer[i++] = cmd.deviceId & 0xff;
    buffer[i++] = (cmd.deviceId >> 8) & 0xff;
    buffer[i++] = (cmd.deviceId >> 16) & 0xff;
    buffer[i++] = (cmd.deviceId >> 24) & 0xff;

    // We fill the buffer with zeroes for the payload
    for (int j = ++i; i < bufferSize; j++) {
        buffer[j] = 0;
    }

    TxBuffer(9);
}