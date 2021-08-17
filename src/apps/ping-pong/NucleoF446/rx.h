#ifndef RX_H__
#define RX_H__

#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "cli.h"
#include "tx.h"
#include "utils.h"

// extern uint16_t testMessageLeft;
// extern uint16_t testmessageCount;
// extern uint16_t testintervalMs;

void ProcessSequenceCommand(uint8_t *buffer) ;
void parseMsg(uint8_t * RfBuffer, uint8_t msgSize);

#endif // RX_H__