#include "radio.h"

#ifndef CONFIG_H__
#define CONFIG_H__

#if defined(REGION_AS923)

#define RF_FREQUENCY 923000000 // Hz

#elif defined(REGION_AU915)

#define RF_FREQUENCY 915000000 // Hz

#elif defined(REGION_CN470)

#define RF_FREQUENCY 470000000 // Hz

#elif defined(REGION_CN779)

#define RF_FREQUENCY 779000000 // Hz

#elif defined(REGION_EU433)

#define RF_FREQUENCY 433000000 // Hz

#elif defined(REGION_EU868)

#define RF_FREQUENCY 868000000 // Hz

#elif defined(REGION_KR920)

#define RF_FREQUENCY 920000000 // Hz

#elif defined(REGION_IN865)

#define RF_FREQUENCY 865000000 // Hz

#elif defined(REGION_US915)

#define RF_FREQUENCY 915000000 // Hz

#elif defined(REGION_RU864)

#define RF_FREQUENCY 864000000 // Hz

#else
#error "Please define a frequency band in the compiler options."
#endif

#define TX_OUTPUT_POWER 14 // dBm

#if defined(USE_MODEM_LORA)

#define LORA_BANDWIDTH 0        // [0: 125 kHz, \
                                    //  1: 250 kHz, \
                                    //  2: 500 kHz, \
                                    //  3: Reserved]
#define LORA_SPREADING_FACTOR 7 // [SF7..SF12]
#define LORA_CODINGRATE 2       // [1: 4/5, \
                                    //  2: 4/6, \
                                    //  3: 4/7, \
                                    //  4: 4/8]
#define LORA_PREAMBLE_LENGTH 8  // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT 5   // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON false
#define LORA_IQ_INVERSION_ON false

#elif defined(USE_MODEM_FSK)

#define FSK_FDEV 25000          // Hz
#define FSK_DATARATE 5000       // bps
#define FSK_BANDWIDTH 50000     // Hz
#define FSK_AFC_BANDWIDTH 83333 // Hz
#define FSK_PREAMBLE_LENGTH 5   // Same for Tx and Rx
#define FSK_FIX_LENGTH_PAYLOAD_ON false

#else
#error "Please define a modem in the compiler options."
#endif

#define RX_TIMEOUT_VALUE 1
#define BUFFER_SIZE 64 // Define the payload size here

#define FIRMWARE_VERSION 0x01020000 // 1.2.0.0

#define GITHUB_VERSION 0x05000000 // 5.0.0.0
#endif
