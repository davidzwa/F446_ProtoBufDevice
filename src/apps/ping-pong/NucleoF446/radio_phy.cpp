#include "radio_phy.h"

#include <stdio.h>

#include "ProtoReadBuffer.h"
#include "ProtoWriteBuffer.h"
#include "cli.h"
#include "config.h"
#include "delay.h"
#include "lora_device_messages.h"
#include "measurements.h"
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
}

void OnTxDone(void) {
    ApplyConfigIfPending();

    UartDebug("LORATX-DONE", 400, 11);
}

void OnTxTimeout(void) {
    ApplyConfigIfPending();

    UartDebug("LORATX-TIMEOUT", 400, 14);
}

void OnRxDone(uint8_t* payload, uint16_t size, int16_t rssi, int8_t snr) {
    // Tracks RSSI and SNR
    lastRssiValue = rssi;
    lastSnrValue = snr;

    for (uint16_t i = 0; i < size; i++) {
        readLoraBuffer.push(payload[i]);
    }

    auto result = loraPhyMessage.deserialize(readLoraBuffer);
    if (result != ::EmbeddedProto::Error::NO_ERRORS) {
        UartSendAck(3);
        Radio.Rx(0);
        return;
    }

    // Processing
    HandleLoRaProtoPayload(loraPhyMessage, rssi, snr);

    Radio.Rx(0);
}

/**
 * @brief Proto processor for LoRa messages - makes testing easier
 *
 */
void HandleLoRaProtoPayload(LORA_MSG_TEMPLATE& message, int16_t rssi, int8_t snr) {
    auto sequenceNumber = message.get_CorrelationCode();
    RegisterNewMeasurement(sequenceNumber, rssi, snr);

    // Debug whether this was multicast or not
    bool isDeviceId = IsDeviceId(message.get_DeviceId());
    if (message.get_IsMulticast()) {
        UartDebug("MC", isDeviceId + 200, 2);
    } else {
        UartDebug("UC", isDeviceId + 100, 2);
    }

    if (message.has_forwardRadioConfigUpdate()) {
        auto configMessage = message.get_forwardRadioConfigUpdate();
        if (configMessage.has_radioRxConfig()) {
            auto config = configMessage.get_radioRxConfig();
            // TODO
            // UpdateRadioRxConfig();
        }
        if (configMessage.has_radioTxConfig()) {
            auto config = configMessage.get_radioTxConfig();
            // TODO apply
            // UpdateRadioTxConfig();
        }
        // if (message.has_sequenceConfig()) {
        //     SetSequenceRequestConfig(message.get_sequenceConfig());

        //     // TODO send ACK if success
        // }
    } else if (message.has_forwardExperimentCommand()) {
        auto msg = message.get_forwardExperimentCommand();
        auto slaveCommand = msg.get_slaveCommand();
        if (slaveCommand == ForwardExperimentCommand::SlaveCommand::ClearFlash) {
            ClearMeasurements();

            if (message.get_IsMulticast()) {
                UartDebug("MCSKIP", 1, 6);
            } else {
                UartDebug("ACK", 1, 3);
                TransmitLoRaFlashInfo(true);
            }

                // UartSendBoot();
            } else if (slaveCommand == ForwardExperimentCommand::SlaveCommand::QueryFlash) {
                if (message.get_IsMulticast()) {
                    UartDebug("MCSKIP", 2, 6);
                } else {
                    UartDebug("ACK", 1, 3);
                    TransmitLoRaFlashInfo(false);
                    // UartSendBoot();
                }
            } else if (slaveCommand == ForwardExperimentCommand::SlaveCommand::StreamFlashContents) {
                // TODO
            }

    } else if (message.has_measurementStreamRequest()) {
        // TODO filter based on device id
        // StreamMeasurements();
    } else if (message.has_rlncInitConfigCommand()) {
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
    auto expResponse = message.mutable_experimentResponse();
    expResponse.set_WasCleared(wasCleared);
    expResponse.set_MeasurementCount(GetMeasurementCount());
    expResponse.set_MeasurementsDisabled(IsStorageDirtyAndLocked());
    
    DelayMs(1);

    TransmitLoRaMessage(message);
}

void TransmitLoRaMessage(LORA_MSG_TEMPLATE& message) {
    message.serialize(writeLoraBuffer);
    Radio.Send(writeLoraBuffer.get_data(), writeLoraBuffer.get_size());
    writeLoraBuffer.clear();
}
