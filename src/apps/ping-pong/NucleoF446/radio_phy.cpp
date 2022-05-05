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

bool HandleLoRaProtoMulticastPayload(LORA_MSG_TEMPLATE& message, int16_t rssi, int8_t snr);
bool HandleRlncCommand(LORA_MSG_TEMPLATE& message);

void TxLoRaAck(int correlationCode);

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
    UartDebug("LORATX_DONE", 200, 11);
    Radio.Rx(0);
}

void OnTxTimeout(void) {
    UartDebug("LORATX_TIMEOUT", 400, 14);
    Radio.Rx(0);
}

void OnRxDone(uint8_t* payload, uint16_t size, int16_t rssi, int8_t snr) {
    // Tracks RSSI and SNR
    lastRssiValue = rssi;
    lastSnrValue = snr;

    UartDebug("LORARX_DONE", 0, 11);

    for (uint16_t i = 0; i < size; i++) {
        readLoraBuffer.push(payload[i]);
    }

    auto result = loraPhyMessage.deserialize(readLoraBuffer);
    if (result != ::EmbeddedProto::Error::NO_ERRORS) {
        UartDebug("PROTO_LORA_FAIL", 401, 15);
        Radio.Rx(0);
        return;
    }

    // Processing
    bool needsRadioRx = false;
    auto isMulticast = loraPhyMessage.get_IsMulticast();
    bool isDeviceId = IsDeviceId(loraPhyMessage.get_DeviceId());
    if (isMulticast) {
        UartDebug("MC", isDeviceId + 200, 2);
        needsRadioRx = HandleLoRaProtoMulticastPayload(loraPhyMessage, rssi, snr);
    } else if (isDeviceId) {
        UartDebug("UC", isDeviceId + 100, 2);
        needsRadioRx = HandleLoRaProtoPayload(loraPhyMessage, rssi, snr);
    }

    // Only specific RLNC messages are registered as measurement
    if (loraPhyMessage.get_which_Body() == LORA_MSG_TEMPLATE::id::NOT_SET || loraPhyMessage.has_rlncInitConfigCommand() || loraPhyMessage.has_rlncEncodedFragment() || loraPhyMessage.has_rlncStateUpdate() || loraPhyMessage.has_rlncTerminationCommand()) {
        uint16_t sequenceNumber = loraPhyMessage.get_CorrelationCode();
        RegisterNewMeasurement(sequenceNumber, rssi, snr);
    }

    // Send the RX event back over UART (if enabled)
    UartSendLoRaRx(loraPhyMessage, rssi, snr, false);

    // Ensure that the static message is not re-used
    readLoraBuffer.clear();
    loraPhyMessage.clear();

    // Re-enable continuous listening
    if (!needsRadioRx) {
        Radio.Rx(0);
    }
}

bool HandleLoRaProtoMulticastPayload(LORA_MSG_TEMPLATE& message, int16_t rssi, int8_t snr) {
    if (message.has_rlncRemoteFlashStopCommand()) {
        StopRlncSessionFromFlash();
    } else if (message.has_deviceConfiguration() && IsSending()) {
        // Broadcast emergency stop command
        StopPeriodicTransmit();
    } 

    // Disabled explicitly due to bad behaviour so far
    // else if (message.has_forwardExperimentCommand()) {
        // auto msg = message.get_forwardExperimentCommand();
        // auto slaveCommand = msg.get_slaveCommand();
        // Debug this before enabling it
        // if (slaveCommand == ForwardExperimentCommand::SlaveCommand::ClearFlash) {
        //     ClearMeasurements();
        // }
    // }
    
    HandleRlncCommand(message);

    return false;
}

/**
 * @brief Proto processor for LoRa messages - makes testing easier
 *
 */
bool HandleLoRaProtoPayload(LORA_MSG_TEMPLATE& message, int16_t rssi, int8_t snr) {
    if (message.has_deviceConfiguration()) {
        auto config = message.get_deviceConfiguration();

        if (config.get_applyTransmitConfig()) {
            // Set the TXRX config
            SetTxRxConfig(config.get_transmitConfiguration(), false);
            UartDebug("TxConf", 0, 6);

            // Ack receipt
            DelayMs(10);
            TxLoRaAck(1);
        }
        else {
            StopPeriodicTransmit();
            UartDebug("DevConfStop", 0, 12);
        }
        
        if (config.get_enableSequenceTransmit()) {
            DelayMs(10);
            TxLoRaAck(2);

            auto preConfigDelay = config.get_sequenceConfiguration().Delay();
            if (preConfigDelay > 0) {
                DelayMs(preConfigDelay);
            }
            TxLoRaAck(3);
            DelayMs(10);

            ApplyAlwaysSendPeriodically(config);
            UartDebug("DevConf", 0, 7);
        }

        return true;
    } else if (message.has_forwardExperimentCommand()) {
        auto msg = message.get_forwardExperimentCommand();
        auto slaveCommand = msg.get_slaveCommand();
        if (slaveCommand == ForwardExperimentCommand::SlaveCommand::ClearFlash) {
            ClearMeasurements();
        }

        UartDebug("LORA_ACK", 1, 8);
        TransmitLoRaFlashInfo(true);
        return true;
    } else if (message.has_rlncRemoteFlashStartCommand()) {
        if (IsRlncSessionStarted()) {
            StopRlncSessionFromFlash();
        }

        StartRlncSessionFromFlash(message.get_rlncRemoteFlashStartCommand());
        SendLoRaRlncSessionResponse();
        return true;
    } else if (message.has_rlncQueryRemoteFlashCommand()) {
        SendLoRaRlncSessionResponse();
        return true;
    }

    HandleRlncCommand(message);
    return false;
}

bool HandleRlncCommand(LORA_MSG_TEMPLATE& message) {
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
    } else {
        return false;
    }

    return true;
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

void TxLoRaAck(int correlationCode) {
    LORA_MSG_TEMPLATE message;
    message.set_CorrelationCode(correlationCode);
    auto& ack = message.mutable_ack();
    ack.set_DeviceId(NETWORK_RESPONSE_ID);

    TransmitLoRaMessage(message);
}

void TransmitLoRaMessage(LORA_MSG_TEMPLATE& message) {
    message.serialize(writeLoraBuffer);
    Radio.Send(writeLoraBuffer.get_data(), writeLoraBuffer.get_size());
    writeLoraBuffer.clear();
}
