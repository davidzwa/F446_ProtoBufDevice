#ifndef RADIO_CONFIG_H
#define RADIO_CONFIG_H

#include "config.h"
#include "radio.h"

void InitRadioTxConfigLoRa();
void InitRadioRxConfigLoRa();
void ApplyRadioTxConfig();
void ApplyRadioRxConfig();

void SetTxPower(int8_t power);
void SetTxConfig(const TransmitConfiguration& config);

#endif  // RADIO_CONFIG_H
