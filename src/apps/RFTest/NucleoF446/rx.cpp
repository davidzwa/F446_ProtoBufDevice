#include "rx.h"

void ProcessSequenceCommand(uint8_t *buffer) {
    uint16_t messageCount = (buffer[1] << 8) + buffer[2];
    uint16_t intervalMs = (buffer[3] << 8) + buffer[4];
    uint32_t deviceId = (buffer[5] << 24) + (buffer[6] << 16) + (buffer[7] << 8) + buffer[8];

    DeviceId_t currentDeviceId = GetDeviceId();

    // deviceId = 0 => multicast
    if (deviceId && currentDeviceId.id0 != deviceId) {
        printf("[rx] Device id0 %lu was not equal to %lu! Command ignored.\n\r", currentDeviceId.id0, deviceId);
    } else {
        if (intervalMs < 150) {
            printf("[rx] Device ID recognized, but intervalMS %d was too low (<150). Ignoring command", intervalMs);
        } else {
            // testMessageLeft = messageCount;
            // testmessageCount = messageCount;
            // testintervalMs = intervalMs;

            printf("[rx] Device id %lu recognized. Test Packets: %d, interval: %d ms\n\r", deviceId, messageCount, intervalMs);

            TxStartSequenceTest(messageCount, intervalMs);
        }
    }
}

void parseMsg(uint8_t *RfBuffer, uint8_t msgSize) {
    switch (RfBuffer[0]) {
        // Set Spreading factor
        case 'S':
            if (msgSize > 1) {
                ProcessSpreadingFactorMessage(RfBuffer[1], true);
            }
            break;

        // Ping
        case 'P':
            TxPing();
            break;

        // Execute sequence cmd
        case 'T':
            if (msgSize > 8) {
                ProcessSequenceCommand(RfBuffer);
            }
            break;

        // parse RF config packet
        case 'F':
            SetNewRFSettings((uint8_t *) RfBuffer, msgSize);
            break;

        default:
            break;
    }
}
