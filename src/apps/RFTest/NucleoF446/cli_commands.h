#include <stdint.h>

#ifndef CLI_COMMANDS_H__
#define CLI_COMMANDS_H__

typedef struct SequenceCommand_s
{
    uint16_t messageCount;
    uint16_t intervalMs;
    uint32_t deviceId;
} SequenceCommand_t;

#endif