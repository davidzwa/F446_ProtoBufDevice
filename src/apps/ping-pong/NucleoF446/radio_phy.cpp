#include "radio_phy.h"

#include <stdio.h>

#include "ProtoReadBuffer.h"
#include "ProtoWriteBuffer.h"
#include "cli.h"
#include "config.h"
#include "delay.h"
#include "lora_device_messages.h"
#include "measurements.h"
#include "nvm_rlnc.h"
#include "radio_config.h"
#include "tasks.h"
#include "utils.h"

ProtoReadBuffer readLoraBuffer;
ProtoWriteBuffer writeLoraBuffer;
LORA_MSG_TEMPLATE loraPhyMessage;

int8_t lastRssiValue = 0;
int8_t lastSnrValue = 0;

/*!
 * \brief Radio interupts
 */
void OnTxDone(void);
void OnRxDone(uint8_t* payload, uint16_t size, int16_t rssi, int8_t snr);
void OnTxTimeout(void);
void OnRxTimeout(void);
void OnRxError(void);

/*!
 * Radio events function pointer
 */
static RadioEvents_t RadioEvents;

uint32_t InitRadioPhy() {
    // Radio initialization
    RadioEvents.TxDone = OnTxDone;
    RadioEvents.RxDone = OnRxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxTimeout = OnRxTimeout;
    RadioEvents.RxError = OnRxError;

    Radio.Init(&RadioEvents);
    Radio.SetChannel(RF_FREQUENCY);

    auto rngSeed = Radio.Random();

#if defined(USE_MODEM_LORA)

    Radio.SetTxConfig(MODEM_LORA, TX_OUTPUT_POWER, 0, LORA_BANDWIDTH,
                      LORA_SPREADING_FACTOR, LORA_CODINGRATE,
                      LORA_PREAMBLE_LENGTH, LORA_FIX_LENGTH_PAYLOAD_ON,
                      LORA_CRC_ON, 0, 0, LORA_IQ_INVERSION_ON, RX_TIMEOUT_VALUE);

    Radio.SetRxConfig(MODEM_LORA, LORA_BANDWIDTH, LORA_SPREADING_FACTOR,
                      LORA_CODINGRATE, 0, LORA_PREAMBLE_LENGTH,
                      LORA_SYMBOL_TIMEOUT, LORA_FIX_LENGTH_PAYLOAD_ON,
                      0, LORA_CRC_ON, 0, 0, LORA_IQ_INVERSION_ON, LORA_CONT_LISTEN);

    Radio.SetMaxPayloadLength(MODEM_LORA, RADIO_BUFFER_SIZE);

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

    return rngSeed;
}

void OnTxDone(void) {
    UartDebug("LORATX-DONE", 200, 11);
    Radio.Rx(0);
}

void OnTxTimeout(void) {
    UartDebug("LORATX-TIMEOUT", 400, 14);
    Radio.Rx(0);
}

void OnRxDone(uint8_t* payload, uint16_t size, int16_t rssi, int8_t snr) {
    // Tracks RSSI and SNR
    lastRssiValue = rssi;
    lastSnrValue = snr;

    UartDebug("LORARX-DONE", 0, 11);

    for (uint16_t i = 0; i < size; i++) {
        readLoraBuffer.push(payload[i]);
    }

    auto result = loraPhyMessage.deserialize(readLoraBuffer);
    if (result != ::EmbeddedProto::Error::NO_ERRORS) {
        UartDebug("PROTO-LORA-FAIL", 401, 15);
        Radio.Rx(0);
        return;
    }

    // Processing
    auto isResponding = HandleLoRaProtoPayload(loraPhyMessage, rssi, snr);

    if (!isResponding) {
        Radio.Rx(0);
    }
}

/**
 * @brief Proto processor for LoRa messages - makes testing easier
 *
 */
bool HandleLoRaProtoPayload(LORA_MSG_TEMPLATE& message, int16_t rssi, int8_t snr) {
    auto hasResponseTx = false;

    // Debug whether this was multicast or not
    bool isDeviceId = IsDeviceId(message.get_DeviceId());
    bool isMulticast = message.get_IsMulticast();
    if (isMulticast) {
        UartDebug("MC", isDeviceId + 200, 2);

        // Only multicast is registered as measurement
        auto sequenceNumber = message.get_CorrelationCode();
        RegisterNewMeasurement(sequenceNumber, rssi, snr);
    } else {
        UartDebug("UC", isDeviceId + 100, 2);
    }

    // Exception for multicast stop command
    if ((!isDeviceId || isMulticast) && message.has_deviceConfiguration()) {
        auto deviceConf = message.get_deviceConfiguration();
        if (IsSending()) {
            StopPeriodicTransmit();
        }
    } else if (isDeviceId) {
        if (message.has_deviceConfiguration()) {
            auto config = message.get_deviceConfiguration();
            if (IsSending()) {
                StopPeriodicTransmit();
                UartDebug("DevConfStop", 0, 12);
            } else {
                SetTxConfig(config.get_transmitConfiguration());
                ApplyAlwaysSendPeriodically(config);
                UartDebug("DevConf", 0, 7);
            }
        } else if (message.has_forwardExperimentCommand()) {
            auto msg = message.get_forwardExperimentCommand();
            auto slaveCommand = msg.get_slaveCommand();
            if (slaveCommand == ForwardExperimentCommand::SlaveCommand::ClearFlash) {
                ClearMeasurements();
            }
            
            // Not built yet
            // if (slaveCommand == ForwardExperimentCommand::SlaveCommand::StreamFlashContents) {
            //     // TODO
            // }

            if (!isMulticast) {
                UartDebug("LORA-ACK", 1, 8);
                hasResponseTx = true;
                TransmitLoRaFlashInfo(true);
            }
        } else if (message.has_rlncRemoteFlashStartCommand()) {
            if (IsRlncSessionStarted()) {
                StopRlncSessionFromFlash();
            } else {
                StartRlncSessionFromFlash(message.get_rlncRemoteFlashStartCommand());
            }
            SendLoRaRlncSessionResponse();
            hasResponseTx = true;
        } else if (message.has_rlncQueryRemoteFlashCommand()) {
            SendLoRaRlncSessionResponse();
            hasResponseTx = true;
        }
        // Not built yet
        // else if (message.has_measurementStreamRequest()) {
        // TODO filter based on device id
        // StreamMeasurements();
        // }
    }

    if (isMulticast && message.has_rlncRemoteFlashStopCommand()) {
        StopRlncSessionFromFlash();
    }

    // MC or UC work the same
    if (message.has_rlncInitConfigCommand()) {
        auto initConfigCommand = message.mutable_rlncInitConfigCommand();
        decoder.InitRlncDecodingSession(initConfigCommand);
    } else if (message.has_rlncStateUpdate()) {
        auto rlncStateUpdate = message.get_rlncStateUpdate();
        decoder.UpdateRlncDecodingState(rlncStateUpdate);
    } else if (message.has_rlncEncodedFragment()) {
        decoder.ProcessRlncFragment(message);
    } else if (message.has_rlncTerminationCommand()) {
        decoder.TerminateRlnc(message.get_rlncTerminationCommand());
    }

    // Send the RX event back over UART (if enabled)
    UartSendLoRaRx(message, rssi, snr, false);

    // Ensure that the message is not re-used
    readLoraBuffer.clear();
    message.clear();

    return hasResponseTx;
}

void OnRxTimeout(void) {
    Radio.Rx(0);
}

void OnRxError(void) {
    Radio.Rx(0);
}

void TransmitLoRaFlashInfo(bool wasCleared) {
    LORA_MSG_TEMPLATE message;
    // Suppress response
    message.set_IsMulticast(false);
    message.set_DeviceId(NETWORK_RESPONSE_ID);
    auto& expResponse = message.mutable_experimentResponse();
    expResponse.set_WasCleared(wasCleared);
    expResponse.set_MeasurementCount(GetMeasurementCount());
    expResponse.set_MeasurementsDisabled(IsStorageDirtyAndLocked());

    TransmitLoRaMessage(message);
}

void TransmitLoRaAck() {
    LORA_MSG_TEMPLATE message;
    auto& ack = message.mutable_ack();
    ack.set_DeviceId(NETWORK_RESPONSE_ID);

    TransmitLoRaMessage(message);
}

void TransmitLoRaMessage(LORA_MSG_TEMPLATE& message) {
    message.serialize(writeLoraBuffer);
    Radio.Send(writeLoraBuffer.get_data(), writeLoraBuffer.get_size());
    writeLoraBuffer.clear();
}
