#include "delay.h"
#include "stdio.h"
#include "tx.h"

uint16_t bufferSize = BUFFER_SIZE;
uint8_t buffer[BUFFER_SIZE];

void TxBuffer()
{
    printf("[TX] '%0xs'\n\r", buffer);
    Radio.Send(buffer, bufferSize);
    DelayMs(1);
}

void TxPing()
{
    // Send the next PING frame
    buffer[0] = 'P';
    buffer[1] = 'I';
    buffer[2] = 'N';
    buffer[3] = 'G';
    
    // We fill the buffer with numbers for the payload
    for (int i = 4; i < bufferSize; i++)
    {
        buffer[i] = i - 4;
    }

    TxBuffer();
}

void TxPong()
{
    // Send the next PING frame
    buffer[0] = 'P';
    buffer[1] = 'O';
    buffer[2] = 'N';
    buffer[3] = 'G';
    // We fill the buffer with numbers for the payload
    for (int i = 4; i < bufferSize; i++)
    {
        buffer[i] = i - 4;
    }

    TxBuffer();
}

void TxSpreadingFactor(uint8_t unicodeValue) {
    // Send the next SF frame
    buffer[0] = 'S';
    buffer[1] = unicodeValue;
    // We fill the buffer with zeroes for the payload
    for (int i = 2; i < bufferSize; i++)
    {
        buffer[i] = 0;
    }

    TxBuffer();
}

void TxSequenceCommand(uint8_t messageCount, uint32_t deviceUuid0) {
    // Send the next T1000 frame
    buffer[0] = 'T';
    buffer[1] = messageCount;
    buffer[2] = (deviceUuid0) & 0xff;
    buffer[3] = (deviceUuid0>>8) & 0xff;
    buffer[4] = (deviceUuid0>>16) & 0xff;
    buffer[5] = (deviceUuid0>>24) & 0xff;
    // We fill the buffer with zeroes for the payload
    for (int i = 6; i < bufferSize; i++)
    {
        buffer[i] = 0;
    }

    TxBuffer();
}