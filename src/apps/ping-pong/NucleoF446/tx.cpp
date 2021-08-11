#include "delay.h"
#include "stdio.h"
#include "tx.h"

uint16_t bufferSize = BUFFER_SIZE;
uint8_t buffer[BUFFER_SIZE];

void TxBuffer()
{
    DelayMs(1);
    printf("TX %s\n\r", buffer);
    Radio.Send(buffer, bufferSize);
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