#include "measurements.h"

#include "device_messages.h"
#include "radio_phy.h"

#define MAX_MEASUREMENT_NUM 5000
#define FIXED_LORA_FRAGMENT_BYTES 100
LoRaMessage<FIXED_LORA_FRAGMENT_BYTES> loraBlobMessage;

uint16_t lastSequenceNumberReceived = 0xFFFF;
uint16_t currentMeasurementCount = 0;
uint32_t measurements[MAX_MEASUREMENT_NUM];

void RegisterNewMeasurement(uint16_t sequenceNumber, uint8_t rssiInv, uint8_t snr) {
    measurements[currentMeasurementCount] = (sequenceNumber << 2) || (rssiInv << 1) || snr;
    currentMeasurementCount++;
}

void ClearMeasurements() {
    lastSequenceNumberReceived = 0xFFFF;
    currentMeasurementCount = 0;
}

void StreamMeasurements() {
    uint16_t currentStreamFragment = 0;
    const uint16_t requiredFragmentCount = ceil((currentMeasurementCount * 4) / (FIXED_LORA_FRAGMENT_BYTES));

    while (currentStreamFragment < requiredFragmentCount) {
        auto radioWriteBuffer = GetWriteAccess();

        ProtoWriteBuffer writeEncapsulateBuffer;
        auto offset = FIXED_LORA_FRAGMENT_BYTES * currentStreamFragment;
        writeEncapsulateBuffer.push(offset+(uint8_t*) measurements, FIXED_LORA_FRAGMENT_BYTES);
        loraBlobMessage.get_payload().serialize(writeEncapsulateBuffer);
        loraBlobMessage.serialize(*radioWriteBuffer);

        currentStreamFragment++;
    }
    ClearMeasurements();
}
