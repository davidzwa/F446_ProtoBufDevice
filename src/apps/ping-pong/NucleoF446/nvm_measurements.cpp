#include "nvm_measurements.h"

#include "nvmm.h"

// #define DEBUG_THROW
// Flash bank 6
#define NVM_PAGE (6)
NvmHandle NvmMeasurements(NVM_PAGE);

// Unloaded state
uint16_t measurementCountState = 0xFFFF;

uint16_t FlashGetValidatedAddress(uint32_t index);
uint16_t FlashWriteMeasurement(uint32_t index, uint32_t value);

uint16_t ClearStorage() {
    uint16_t result = NvmMeasurements.Clear();
    if (result != 0x00) {
#ifdef DEBUG_THROW
        throw "ERR";
#endif
        return CLEAR_ERROR;
    }

    measurementCountState = 0x0000;

    return 0;
}

uint16_t AppendMeasurement(uint32_t value) {
    uint32_t index = GetMeasurementCount();
    uint16_t resultWrite = FlashWriteMeasurement(index, value);
    if (resultWrite != 0x00) {
#ifdef DEBUG_THROW
        throw "ERR";
#endif
        return resultWrite;
    }
    
    measurementCountState++;

    return 0x00;
}

uint16_t FlashWriteMeasurement(uint32_t index, uint32_t value) {
    // Validate value is erased
    uint32_t flashValue;
    uint16_t result = ReadMeasurement(index, &flashValue);
    if (result != 0x00) {
#ifdef DEBUG_THROW
        throw "ERR";
#endif
        return READ_ERROR;
    }
    if (flashValue != 0xFFFFFFFF) {
#ifdef DEBUG_THROW
        throw "ERR";
#endif
        return ADDRESS_ALREADY_WRITTEN;
    }

    uint32_t addressOrError = FlashGetValidatedAddress(index);
    if (addressOrError >= DATA_SECTOR_END) return addressOrError;

    return NvmMeasurements.Write(addressOrError, value);
}

/**
 * @brief Reads from flash returning HAL_OK (0) or higher
 * 
 * @param index 
 * @param value 
 * @return uint16_t success (0) or not (>0)
 */
uint16_t ReadMeasurement(uint32_t index, uint32_t* target) {
    uint32_t address = FlashGetValidatedAddress(index);

    return NvmMeasurements.Read32(address, target);
}

uint16_t FlashGetValidatedAddress(uint32_t index) {
    uint32_t address = DATA_SECTOR_BASE + index;

    if (address >= DATA_SECTOR_BASE && address < DATA_SECTOR_END) {
        return address;
    }

#ifdef DEBUG_THROW
    throw "ERR";
#endif
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
        uint16_t result = NvmMeasurements.Read32(valueAtIndex, &target);
        if (result) return 0xFFFF;

        if (target == 0xFFFFFFFF) break;

        measurementCountState++;
        valueAtIndex++;
    }

    return measurementCountState;
}
