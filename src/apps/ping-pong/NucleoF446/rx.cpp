#include "stdint.h"
#include "string.h"
#include "cli.h"

const uint8_t SFMsg[] = "S";

bool IsSpreadingFactorConfig(const char *buffer)
{
    return strncmp((const char *)buffer, (const char *)SFMsg, 1) == 0;
}

void ProcessMode(const char *buffer)
{
    if (buffer[0] == 'S'){
        ProcessSpreadingFactorMessage((uint8_t) buffer[1], false);
    }
}