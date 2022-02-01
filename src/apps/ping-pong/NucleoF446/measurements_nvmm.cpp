#include "measurements_nvmm.h"

#include "nvmm.h"

// Unloaded state
uint16_t measurementCountState = 0xFFFF;

uint16_t FlashGetValidatedAddress(uint32_t index);
uint16_t FlashWriteMeasurement(uint32_t index, uint32_t value);

uint16_t ClearStorage() {
    uint16_t result = NvmmClear();
    if (result != 0x00) {
        return CLEAR_ERROR;
    }

    measurementCountState = 0xFFFF;

    return 0;
}

uint16_t AppendMeasurement(uint32_t value) {
    uint32_t index = GetMeasurementCount();
    uint16_t resultWrite = FlashWriteMeasurement(index, value);
    if (resultWrite != 0x00) {
        return resultWrite;
    }
    
    measurementCountState++;

    return 0x00;
}

uint16_t FlashWriteMeasurement(uint32_t index, uint32_t value) {
    // Validate value is erased
    uint32_t flashValue;
    uint16_t result = FlashReadMeasurement(index, &flashValue);
    if (result != 0x00) {
        return READ_ERROR;
    }
    if (flashValue != 0xFFFFFFFF) {
        return ADDRESS_ALREADY_WRITTEN;
    }

    uint32_t addressOrError = FlashGetValidatedAddress(index);
    if (addressOrError >= DATA_SECTOR_END) return addressOrError;

    return NvmmWriteVar32(addressOrError, value);
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

/**
 * @brief Get the Measurement Count by looping over existing flash and counting non-FFFFFFFF values
 * 
 * @return uint32_t 
 */
uint32_t GetMeasurementCount() {
    // Return cached value if not unset
    if (measurementCountState != 0xFFFF) {
        return measurementCountState;
    }

    uint16_t valueAtIndex = DATA_SECTOR_BASE;
    uint32_t target;
    measurementCountState = 0;
    while (valueAtIndex < DATA_SECTOR_END) {
        uint16_t result = NvmmReadVar32(valueAtIndex, &target);
        if (!result) break;

        if (target == 0xFFFFFFF) break;

        measurementCountState++;
        valueAtIndex++;
    }

    return measurementCountState;
}
