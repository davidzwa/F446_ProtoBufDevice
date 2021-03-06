#include "radio.h"
#include "lora_device_messages.h"

#ifndef CONFIG_H__
#define CONFIG_H__

#define APP_NAME "LoRaMulticast"

#if defined(REGION_EU433)
#define RF_FREQUENCY 433000000 // Hz
#elif defined(REGION_EU868)
#define RF_FREQUENCY 872000000 // Hz
#else
#error "Please define a frequency band in the compiler options."
#endif

#define TX_OUTPUT_POWER 14 // dBm [-17 to 14]

#if defined(USE_MODEM_LORA)

#define LORA_BANDWIDTH 2        // [0: 125 kHz, \
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
#define LORA_CRC_ON true
#define LORA_CONT_LISTEN true

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

// Protobuf defines
#define MAX_LORA_BYTES (35)
#define LORA_MSG_TEMPLATE LoRaMessage<MAX_LORA_BYTES>

// RLNC defines
#define LFSR_DEFAULT_SEED 0x08

#define RX_TIMEOUT_VALUE 1000
#define RADIO_BUFFER_SIZE 100  // Define the payload size here

#define NETWORK_RESPONSE_ID 0x12345678
#define FIRMWARE_VERSION 0x03060100
#endif
