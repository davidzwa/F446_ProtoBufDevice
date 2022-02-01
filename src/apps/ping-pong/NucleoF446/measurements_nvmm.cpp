#include "measurements_nvmm.h"

#include "nvmm.h"

uint16_t FlashGetValidatedAddress(uint32_t index);
uint16_t SetMeasurementCount(uint32_t newCount);

uint16_t RunFlashDiag() {
    return 0;
}

/**
 * @brief Whether headers required for measurement storage are valid
 * 
 * @return uint16_t (0: correct, 1: READ_ERROR or CORRUPT_MEASUREMENT_COUNTERS)
 */
uint16_t IsStorageValid(){
    uint32_t count = GetMeasurementCount();

    return count == READ_ERROR || count == CORRUPT_MEASUREMENT_COUNTERS;
}

uint16_t ClearStorage() {
    // Quite a hefty operation
    uint16_t result = NvmmClear();
    if (result != 0x00) {
        return CLEAR_ERROR;
    }

    uint16_t measurementCounterWriteResult = SetMeasurementCount(0);
    if (measurementCounterWriteResult != 0x00) {
        return MEASUREMENT_COUNTERS_UPDATE_ERROR;
    }

    return 0;
}

uint16_t IsStorageFull() {
    uint32_t count = GetMeasurementCount();
    if (count == READ_ERROR || count == CORRUPT_MEASUREMENT_COUNTERS) {
        return count;
    }

    if (count >= MAX_MEASUREMENT_NUM) {
        return true;
    } else {
        return false;
    }
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

uint16_t SetMeasurementCount(uint32_t newCount) {
    uint16_t status = NvmmWriteVar32(MEASUREMENT_COUNTER, newCount);
    uint16_t statusBackup = NvmmWriteVar32(MEASUREMENT_COUNTER_BACKUP, newCount);

    if (!status && !statusBackup) return 0; // Success
    return 1; // Failure
}

uint16_t AppendMeasurement(uint32_t value) {
    uint32_t currentCount = GetMeasurementCount();

    return FlashWriteMeasurement(currentCount, value);
}

uint16_t FlashWriteMeasurement(uint32_t index, uint32_t value) {
    uint32_t currentCount = GetMeasurementCount();

    if (currentCount == READ_ERROR || currentCount == CORRUPT_MEASUREMENT_COUNTERS) {
        return currentCount;
    }

    // As currentCount is zero-based we need not increment it yet
    uint32_t addressOrError = FlashGetValidatedAddress(currentCount);
    if (addressOrError > DATA_SECTOR_END) return addressOrError;

    uint32_t flashValue;
    uint16_t result = FlashReadMeasurement(addressOrError, &flashValue);

    if (result != 0x00) {
        return READ_ERROR;
    }

    // Erroneous state, cant overwrite previous measurement or flash not erased before use
    if (flashValue != 0xFFFFFFFF) {
        return ADDRESS_ALREADY_WRITTEN;
    }

    uint16_t resultWrite = NvmmWriteVar32(addressOrError, value);
    if (resultWrite != 0x00) {
        return WRITE_ERROR;
    }

    currentCount++;
    uint16_t counterWriteResult = SetMeasurementCount(currentCount);
    if (counterWriteResult != 0x00) return MEASUREMENT_COUNTERS_UPDATE_ERROR;
    return 0x00;
}

/**
 * @brief Reads from flash returning HAL_OK (0) or higher
 * 
 * @param index 
 * @param value 
 * @return uint16_t success (0) or not (>0)
 */
uint16_t FlashReadMeasurement(uint32_t index, uint32_t* value) {
    uint32_t address = FlashGetValidatedAddress(index);

    return NvmmReadVar32(address, value);
}

uint16_t FlashGetValidatedAddress(uint32_t index) {
    uint32_t address = DATA_SECTOR_BASE + index;

    if (address >= DATA_SECTOR_BASE && address < DATA_SECTOR_END) {
        return address;
    }

    return ADDRESS_OUT_OF_BOUNDS;
}
