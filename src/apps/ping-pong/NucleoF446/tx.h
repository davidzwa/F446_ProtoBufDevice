#include "radio.h"
#include "config.h"
#include "cli_commands.h"

#ifndef TX_H__
#define TX_H__

extern uint16_t bufferSize;
extern uint8_t buffer[BUFFER_SIZE];

void TxBuffer();
void TxPing();
void TxPong();
void TxSpreadingFactor(uint8_t value);
void TxSequenceCommand(SequenceCommand_t command);

#endif // TX_H__