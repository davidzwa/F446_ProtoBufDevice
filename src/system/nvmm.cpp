/*!
 * \file      nvmm.c
 *
 * \brief     None volatile memory management module
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2020 Semtech
 *
 *               ___ _____ _   ___ _  _____ ___  ___  ___ ___
 *              / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 *              \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 *              |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 *              embedded.connectivity.solutions===============
 *
 * \endcode
 */

#include "nvmm.h"

#include "utilities.h"

NvmHandle::NvmHandle(uint8_t pageId) {
    this->pageId = pageId;
}

uint16_t NvmHandle::Write(uint16_t address32, uint32_t variable) {
    return EepromMcuWriteVariable32(pageId, address32 * 0x04, variable);
}

uint16_t NvmHandle::Read(uint16_t address32, uint32_t* variable) {
    return EepromMcuReadVariable32(pageId, address32 * 0x04, variable);
}

bool NvmHandle::Clear() {
    return EepromMcuClearPage(pageId);
}

// bool NvmmCrc32Check(uint16_t size, uint16_t address) {
//     uint8_t data = 0;
//     uint32_t calculatedCrc32 = 0;
//     uint32_t readCrc32 = 0;

//     if (NvmmRead((uint8_t*)&readCrc32, sizeof(readCrc32),
//                  (address + (size - sizeof(readCrc32)))) == sizeof(readCrc32)) {
//         // Calculate crc
//         calculatedCrc32 = Crc32Init();
//         for (uint16_t i = 0; i < (size - sizeof(readCrc32)); i++) {
//             if (NvmmRead(&data, 1, address + i) != 1) {
//                 return false;
//             }
//             calculatedCrc32 = Crc32Update(calculatedCrc32, &data, 1);
//         }
//         calculatedCrc32 = Crc32Finalize(calculatedCrc32);

//         if (calculatedCrc32 != readCrc32) {
//             return false;
//         }
//     }
//     return true;
// }

// bool NvmmReset(uint16_t size, uint16_t offset) {
//     uint32_t crc32 = 0;

//     if (EepromMcuWriteBuffer(offset + size - sizeof(crc32),
//                              (uint8_t*)&crc32, sizeof(crc32)) == LMN_STATUS_OK) {
//         return true;
//     }
//     return false;
// }
