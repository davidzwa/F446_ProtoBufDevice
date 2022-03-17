#include "Crc8.h"

const uint8_t poly = 0xd5;

uint8_t ComputeChecksum(uint8_t* data, uint8_t len) {
    uint8_t crc = 0xff;
    uint8_t i, j;
    for (i = 0; i < len; i++) {
        crc ^= data[i];
        for (j = 0; j < 8; j++) {
            if ((crc & 0x80) != 0)
                crc = (uint8_t)((crc << 1) ^ poly);
            else
                crc <<= 1;
        }
    }
    return crc;
}
