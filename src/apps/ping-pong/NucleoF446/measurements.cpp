#include "measurements.h"

#include "delay.h"
#include "device_messages.h"
#include "radio_phy.h"

#define FIXED_LORA_FRAGMENT_BYTES 100
LoRaMessage<FIXED_LORA_FRAGMENT_BYTES> loraBlobMessage;
uint16_t lastSequenceNumberReceived = 0xFFFF;
bool storageDirtyMeasurementDisabled = false;

/**
 * @brief Check if storage contains 
 * 
 */
void InitializeMeasurements() {
    storageDirtyMeasurementDisabled = (GetMeasurementCount() != 0x00);
}

void RegisterNewMeasurement(uint16_t sequenceNumber, int16_t rssi, int8_t snr) {
    if (storageDirtyMeasurementDisabled) return;
    
    // Compress the value in 32 bits 
    // TODO

    // Store it in flash
    // AppendMeasurement(0x000);
    // TODO
}

void ClearMeasurements() {
    lastSequenceNumberReceived = 0xFFFF;
    ClearStorage();
}

/**
 * Request another device to stream its measurements
 * */
void RequestStreamMeasurements(/*DeviceId*/) {
    loraBlobMessage.clear();
    loraBlobMessage.set_command(::LoRaMessage<FIXED_LORA_FRAGMENT_BYTES>::CommandType::MeasurementStreamRequest);
    loraBlobMessage.set_SequenceNumber(0xFFFE);

    auto radioWriteBuffer = GetWriteAccess();
    loraBlobMessage.serialize(*radioWriteBuffer);
    TransmitProtoBufferInternal();
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
