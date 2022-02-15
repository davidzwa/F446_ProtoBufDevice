#include "measurements.h"

#include "delay.h"
#include "experiment_config.h"
#include "lora_device_messages.h"
#include "radio_phy.h"

LORA_MSG_TEMPLATE loraMessage;
uint16_t lastSequenceNumberReceived = 0xFFFF;
bool isStorageDirtyAndLocked = false;

/**
 * @brief Check if storage contains 
 * 
 */
void InitializeMeasurements() {
    isStorageDirtyAndLocked = (GetMeasurementCount() != 0x00);
}

bool IsStorageDirtyAndLocked() {
    return isStorageDirtyAndLocked;
}

void RegisterNewMeasurement(uint16_t sequenceNumber, int16_t rssi, int8_t snr) {
    // Relocate rssi range of values so it fits in 8 bits
    uint8_t rssi150 = (uint8_t)(rssi + 150);

    // Confine the data in 32 bits
    uint32_t measurement = (uint32_t)(sequenceNumber << 16) + (int16_t)(rssi150 << 8) + (int8_t)snr;

    if (isStorageDirtyAndLocked) return;

    // Store it in flash
    AppendMeasurement(measurement);
}

void ClearMeasurements() {
    lastSequenceNumberReceived = 0xFFFF;
    isStorageDirtyAndLocked = false;
    ClearStorage();
}

/**
 * Request another device to stream its measurements
 * */
void RequestStreamMeasurements(/*DeviceId*/) {
    loraMessage.clear();
    loraMessage.set_CorrelationCode(0xFFFE);
    auto body = loraMessage.mutable_measurementStreamRequest();
    body.set_FragmentSizeMax(MEASUREMENT_FRAGMENT_SIZE);

    TransmitLoRaMessage(loraMessage);
}

void StreamMeasurements() {
    // uint16_t currentStreamFragment = 0;
    // const uint16_t requiredFragmentCount = 1 + floor((currentMeasurementCount * 4) / (FIXED_LORA_FRAGMENT_BYTES));

    // while (currentStreamFragment < requiredFragmentCount) {
    //     ProtoWriteBuffer writeEncapsulateBuffer;
    //     auto offset = FIXED_LORA_FRAGMENT_BYTES * currentStreamFragment;
    //     writeEncapsulateBuffer.push(offset + (uint8_t*)measurements, FIXED_LORA_FRAGMENT_BYTES);
    //     loraBlobMessage.clear();
    //     loraBlobMessage.set_SequenceNumber(currentStreamFragment);
    //     auto result = loraBlobMessage.get_payload()
    //                       .serialize(writeEncapsulateBuffer);
    //     if (result == EmbeddedProto::Error::BUFFER_FULL) {
    //         return;
    //     }

    //     loraBlobMessage.set_command(::LoRaMessage<FIXED_LORA_FRAGMENT_BYTES>::CommandType::MeasurementStreamFragmentReply);

    //     // Take over transmission from radio
    //     auto radioWriteBuffer = GetWriteAccess();
    //     loraBlobMessage.serialize(*radioWriteBuffer);
    //     TransmitProtoBufferInternal();

    //     // Should wait long packet
    //     DelayMs(200);

    //     currentStreamFragment++;
    // }
    // ClearMeasurements();
}
