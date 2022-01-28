#include "measurements_nvmm.h"

#include "nvmm.h"

uint16_t IsStorageValid() {
}

uint16_t IsStorageFull() {
}

uint32_t GetMeasurementCount() {
    uint32_t measurementCount, measurementCountBackup;
    uint16_t status = NvmmReadVar32(MEASUREMENT_COUNTER, &measurementCount);
    uint16_t statusBackup = NvmmReadVar32(MEASUREMENT_COUNTER_BACKUP, &measurementCountBackup);

    if (status != 0 || statusBackup != 0) {
        return READ_ERROR;
    }

    if (measurementCount != measurementCountBackup) {
        return CORRUPT_MEASUREMENT_COUNTERS;
    }

    return measurementCount;
}

uint16_t FlashWriteMeasurement(uint32_t index, uint32_t value) {
}

uint16_t FlashReadMeasurement(uint32_t index, uint32_t value) {
}
