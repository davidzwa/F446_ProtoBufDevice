#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "cli.h"

const uint8_t SFMsg[] = "S";
const uint8_t SequenceCommandMsg[] = "T";

bool IsSpreadingFactorConfig(const char *buffer)
{
    return strncmp((const char *)buffer, (const char *)SFMsg, 1) == 0;
}

bool IsSequenceCommand(const char *buffer)
{
    return strncmp((const char *)buffer, (const char *)SequenceCommandMsg, 1) == 0;
}

void LoRaProcessMode(const char *buffer)
{
    if (IsSpreadingFactorConfig(buffer))
    {
        ProcessSpreadingFactorMessage((uint8_t)buffer[1], false);
    }
    else if (IsSequenceCommand(buffer))
    {
        ProcessSequenceCommand(buffer);
    }
    else
    {
        printf("Config parameter '%c' not recognized\n\r", buffer[0]);
    }
}