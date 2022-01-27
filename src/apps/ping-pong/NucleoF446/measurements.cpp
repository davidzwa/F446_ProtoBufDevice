#include "measurements.h"

#include "delay.h"
#include "device_messages.h"
#include "radio_phy.h"

// 4000 32-bit values in sector, 1 for header, 2 reserved for future use and 2 for counting (both containing same value for safety checks)
#define MAX_MEASUREMENT_NUM (4000 - 5) 
#define FIXED_LORA_FRAGMENT_BYTES 100
LoRaMessage<FIXED_LORA_FRAGMENT_BYTES> loraBlobMessage;

uint16_t lastSequenceNumberReceived = 0xFFFF;
uint16_t currentMeasurementCount = 0;
uint32_t measurements[MAX_MEASUREMENT_NUM];

void RegisterNewMeasurement(uint16_t sequenceNumber, uint8_t rssiInv, uint8_t snr) {
    if (currentMeasurementCount >= (MAX_MEASUREMENT_NUM - 1)) return;

    measurements[currentMeasurementCount] = (sequenceNumber << 2) || (rssiInv << 1) || snr;
    currentMeasurementCount++;
}

void ClearMeasurements() {
    lastSequenceNumberReceived = 0xFFFF;
    currentMeasurementCount = 0;
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
    uint16_t currentStreamFragment = 0;
    const uint16_t requiredFragmentCount = 1 + floor((currentMeasurementCount * 4) / (FIXED_LORA_FRAGMENT_BYTES));

    while (currentStreamFragment < requiredFragmentCount) {
        ProtoWriteBuffer writeEncapsulateBuffer;
        auto offset = FIXED_LORA_FRAGMENT_BYTES * currentStreamFragment;
        writeEncapsulateBuffer.push(offset + (uint8_t*)measurements, FIXED_LORA_FRAGMENT_BYTES);
        loraBlobMessage.clear();
        loraBlobMessage.set_SequenceNumber(currentStreamFragment);
        auto result = loraBlobMessage.get_payload()
                          .serialize(writeEncapsulateBuffer);
        if (result == EmbeddedProto::Error::BUFFER_FULL) {
            return;
        }

        loraBlobMessage.set_command(::LoRaMessage<FIXED_LORA_FRAGMENT_BYTES>::CommandType::MeasurementStreamFragmentReply);

        // Take over transmission from radio
        auto radioWriteBuffer = GetWriteAccess();
        loraBlobMessage.serialize(*radioWriteBuffer);
        TransmitProtoBufferInternal();

        // Should wait long packet
        DelayMs(200);

        currentStreamFragment++;
    }
    ClearMeasurements();
}
