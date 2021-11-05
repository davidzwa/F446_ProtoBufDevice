from cobs import cobs
import time
from gateway import Gateway
from radio_config import RadioConfig
import keyboard

def setNewRFsettings(gateway, rfSettings, broadcast=True):
    if broadcast:
        cmd = b'F' + bytes(rfSettings) + b'\r'
    else:
        cmd = b'G' + bytes(rfSettings) + b'\r'

    print(cmd)
    gateway.write(cmd)


if __name__ == '__main__':

    localGateway = Gateway('COM3', 921600)
    localGateway.openSerial()

    # rfSettings = RadioConfig.getDefaultLoRaConfig()

    # encoded = cobs.encode(bytearray(b'Hello world\x00This is a test\x00'))
    encoded = cobs.encode(bytearray(b'Hello world\x00This is a test'))
    # print("COBS data", encoded)

    # localGateway.write(encoded)
    localGateway.write(bytes("ABCDEF\n\r", "utf-8"))

    while True:
        print(localGateway.readLine())
