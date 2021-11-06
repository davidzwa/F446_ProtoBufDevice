#include "radio.h"

#ifndef RADIO__H__
#define RADIO__H__

typedef struct __attribute__((__packed__)) RadioTXConfig_s {
    RadioModems_t Modem;
    int8_t Power;
    uint32_t Fdev;  // FSK
    uint32_t Bandwidth;
    uint32_t DataRate;
    uint8_t CodeRate;
    uint16_t PreambleLen;
    bool FixLen;
    bool CrcOn;
    bool FreqHopOn;
    uint8_t HopPeriod;
    bool IqInverted;
    uint32_t Timeout;
} RadioTXConfig_t;

typedef struct __attribute__((__packed__)) RadioRXConfig_s {
    RadioModems_t Modem;
    uint32_t Bandwidth;
    uint32_t DataRate;
    uint8_t CodeRate;
    uint32_t BandwidthAfc;  // FSK
    uint16_t PreambleLen;
    uint16_t SymbTimeout;  // (FSK: bytes, LoRa: symbols)
    bool FixLen;
    uint8_t PayloadLen;
    bool CrcOn;
    bool FreqHopOn;
    uint8_t HopPeriod;
    bool IqInverted;
    bool RxContinuous;
} RadioRXConfig_t;

#endif
