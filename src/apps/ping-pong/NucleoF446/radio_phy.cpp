#include "radio_phy.h"

#include <stdio.h>

#include "ProtoReadBuffer.h"
#include "ProtoWriteBuffer.h"
#include "cli.h"
#include "config.h"
#include "device_messages.h"
#include "tasks.h"
#include "uart_messages.h"

// uint16_t msgSize = BUFFER_SIZE;
ProtoReadBuffer readLoraBuffer;
ProtoWriteBuffer writeLoraBuffer;
LoRaMessage<MAX_PAYLOAD_LENGTH> loraPhyMessage;

int8_t lastRssiValue = 0;
int8_t lastSnrValue = 0;

/*!
 * \brief Radio interupts
 */
void OnTxDone(void);
void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr);
void OnTxTimeout(void);
void OnRxTimeout(void);
void OnRxError(void);

/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

void InitRadioPhy() {
    // Radio initialization
    RadioEvents.TxDone = OnTxDone;
    RadioEvents.RxDone = OnRxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxTimeout = OnRxTimeout;
    RadioEvents.RxError = OnRxError;

    Radio.Init(&RadioEvents);
    Radio.SetChannel(RF_FREQUENCY);

#if defined(USE_MODEM_LORA)

    Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                      LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, LORA_IQ_INVERSION_ON, 3000);

    Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                      LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                      LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                      0, true, 0, 0, LORA_IQ_INVERSION_ON, true);

    Radio.SetMaxPayloadLength(MODEM_LORA, BUFFER_SIZE);

#elif defined(USE_MODEM_FSK)

    Radio.SetTxConfig(MODEM_FSK, TX_OUTPUT_POWER, FSK_FDEV, 0,
                      FSK_DATARATE, 0,
                      FSK_PREAMBLE_LENGTH, FSK_FIX_LENGTH_PAYLOAD_ON,
                      true, 0, 0, 0, 3000);

    Radio.SetRxConfig(MODEM_FSK, FSK_BANDWIDTH, FSK_DATARATE,
                      0, FSK_AFC_BANDWIDTH, FSK_PREAMBLE_LENGTH,
                      0, FSK_FIX_LENGTH_PAYLOAD_ON, 0, true,
                      0, 0, false, true);

    Radio.SetMaxPayloadLength(MODEM_FSK, BUFFER_SIZE);

#else
#error "Please define a frequency band in the compiler options."
#endif
}

void OnTxDone(void) {
    ApplyConfigIfPending();

    // if (!isExecutingCommand) {
    //     Radio.Rx(RX_TIMEOUT_VALUE);
    // } else {
    Radio.Sleep();
    // }
}

void OnTxTimeout(void) {
    ApplyConfigIfPending();

    // if (!isExecutingCommand) {
    //     Radio.Rx(RX_TIMEOUT_VALUE);
    // } else {
    Radio.Sleep();
    // }
}

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr) {
    // Tracks RSSI and SNR
    lastRssiValue = rssi;
    lastSnrValue = snr;

    for (uint16_t i = 0; i < size; i++) {
        readLoraBuffer.push(payload[i]);
    }

    auto result = loraPhyMessage.deserialize(readLoraBuffer);
    if (result != ::EmbeddedProto::Error::NO_ERRORS) {
        UartSendAck(3);
        Radio.Rx(RX_TIMEOUT_VALUE);
        return;
    }

    if (loraPhyMessage.get_command() == LoRaMessage<MAX_PAYLOAD_LENGTH>::CommandType::Configuration) {
        if (loraPhyMessage.has_spreadingFactorConfig()) {
            auto config = loraPhyMessage.get_spreadingFactorConfig();
            UpdateRadioSpreadingFactor(config.get_spreadingFactorRx(), config.get_spreadingFactorTx(), true);
        }
        if (loraPhyMessage.has_sequenceRequestConfig()) {
            SetSequenceRequestConfig(loraPhyMessage.get_sequenceRequestConfig());

            // TODO send ACK if success
        }
    }

    // Ensure that the message is not re-used
    auto sequenceNumber = loraPhyMessage.get_SequenceNumber();
    UartSendLoRaRx(loraPhyMessage.get_payload(), sequenceNumber, rssi, snr);
    readLoraBuffer.clear();
    loraPhyMessage.clear();
    Radio.Rx(RX_TIMEOUT_VALUE);
}

void OnRxTimeout(void) {
    Radio.Rx(RX_TIMEOUT_VALUE);
}

void OnRxError(void) {
    Radio.Rx(RX_TIMEOUT_VALUE);
}

void TransmitProtoBuffer() {
    Radio.Send(writeLoraBuffer.get_data(), writeLoraBuffer.get_size());
}

void TransmitUnicast(TransmitCommand<MAX_PAYLOAD_LENGTH> command) {
    loraPhyMessage.clear();
    loraPhyMessage.set_command(::LoRaMessage<MAX_PAYLOAD_LENGTH>::CommandType::UniCast);
    loraPhyMessage.set_payload(command.get_Payload());
    loraPhyMessage.set_SequenceNumber(command.get_SequenceNumber());
    
    auto result = loraPhyMessage.serialize(writeLoraBuffer);
    if (result == ::EmbeddedProto::Error::NO_ERRORS) {
        TransmitProtoBuffer();
    }
}

void TransmitSpreadingFactorConfig(uint8_t spreadingFactor) {
    loraPhyMessage.clear();
    loraPhyMessage.mutable_spreadingFactorConfig().set_spreadingFactorRx(spreadingFactor);
    loraPhyMessage.mutable_spreadingFactorConfig().set_spreadingFactorTx(spreadingFactor);

    auto result = loraPhyMessage.serialize(writeLoraBuffer);
    if (result == ::EmbeddedProto::Error::NO_ERRORS) {
        TransmitProtoBuffer();
    }
}

void TransmitSequenceRequest() {
    loraPhyMessage.clear();

    auto sequenceConfig = loraPhyMessage.mutable_sequenceRequestConfig();
    sequenceConfig.set_DeviceId(0x00);
    sequenceConfig.set_Interval(500);
    sequenceConfig.set_MessageCount(5);

    auto result = sequenceConfig.serialize(writeLoraBuffer);
    if (result == ::EmbeddedProto::Error::NO_ERRORS) {
        TransmitProtoBuffer();
    }
}
