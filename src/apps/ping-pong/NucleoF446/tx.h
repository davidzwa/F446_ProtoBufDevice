#include "radio.h"
#include "config.h"

#ifndef TX_H__ 
#define TX_H__ 

extern uint16_t bufferSize;
extern uint8_t buffer[BUFFER_SIZE];

void TxBuffer();
void TxPing();
void TxPong();
void TxSpreadingFactor(uint8_t value);

#endif // TX_H__