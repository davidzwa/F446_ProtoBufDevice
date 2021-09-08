import serial
import ctypes

ON = 1
OFF = 0

MODEM_FSK = 0
MODEM_LORA  = 1

LORA_BANDWIDTH_125KHZ = 0
LORA_BANDWIDTH_250KHZ = 1
LORA_BANDWIDTH_500KHZ = 2

LORA_CODINGRATE_5 = 1
LORA_CODINGRATE_6 = 2
LORA_CODINGRATE_7 = 3
LORA_CODINGRATE_8 = 4


class RfConfigMsg(ctypes.Structure):
    _fields_ = (
        ('tx_Modem', ctypes.c_uint8),
        ('tx_Power', ctypes.c_uint8),
        ('tx_Fdev', ctypes.c_uint32),
        ('tx_Bandwidth', ctypes.c_uint32),
        ('tx_SpreadingFactor', ctypes.c_uint32),
        ('tx_CodeRate', ctypes.c_uint8),
        ('tx_PreambleLen', ctypes.c_uint16),
        ('tx_FixLen', ctypes.c_uint8),
        ('tx_CrcOn', ctypes.c_uint8),
        ('tx_FreqHopOn', ctypes.c_uint8),
        ('tx_HopPeriod', ctypes.c_uint8),
        ('tx_IqInverted', ctypes.c_uint8),
        ('tx_Timeout', ctypes.c_uint32),
        ('rx_Modem', ctypes.c_uint8),
        ('rx_Bandwidth', ctypes.c_uint32),
        ('rx_SpreadingFactor', ctypes.c_uint32),
        ('rx_CodeRate', ctypes.c_uint8),
        ('rx_BandwidthAfc', ctypes.c_uint32),
        ('rx_PreambleLen', ctypes.c_uint16),
        ('rx_FixLen', ctypes.c_uint8),
        ('rx_PayloadLen', ctypes.c_uint8),
        ('rx_CrcOn', ctypes.c_uint8),
        ('rx_FreqHopOn', ctypes.c_uint8),
        ('rx_HopPeriod', ctypes.c_uint8),
        ('rx_IqInverted', ctypes.c_uint8),
        ('rx_RxContinuous', ctypes.c_uint8)
    )

def getDefaultLoRaConfig():
    rfSettingsStruct = RfConfigMsg()

    # rfSettingsStruct.tx_Modem           = MODEM_LORA
    # rfSettingsStruct.tx_Power           = 14
    # rfSettingsStruct.tx_Fdev            = 0
    # rfSettingsStruct.tx_Bandwidth       = LORA_BANDWIDTH_125KHZ
    # rfSettingsStruct.tx_SpreadingFactor = 7
    # rfSettingsStruct.tx_CodeRate        = LORA_CODINGRATE_6
    # rfSettingsStruct.tx_PreambleLen     = 8
    # rfSettingsStruct.tx_FixLen          = OFF
    # rfSettingsStruct.tx_CrcOn           = OFF
    # rfSettingsStruct.tx_FreqHopOn       = OFF
    # rfSettingsStruct.tx_HopPeriod       = 0
    # rfSettingsStruct.tx_IqInverted      = OFF
    # rfSettingsStruct.tx_Timeout         = 0
    #
    # rfSettingsStruct.rx_Modem           = MODEM_LORA
    # rfSettingsStruct.rx_Bandwidth       = LORA_BANDWIDTH_125KHZ
    # rfSettingsStruct.rx_SpreadingFactor = 7
    # rfSettingsStruct.rx_CodeRate        = LORA_CODINGRATE_6
    # rfSettingsStruct.rx_BandwidthAfc    = 0
    # rfSettingsStruct.rx_PreambleLen     = 8
    # rfSettingsStruct.rx_FixLen          = OFF
    # rfSettingsStruct.rx_PayloadLen      = 0
    # rfSettingsStruct.rx_CrcOn           = OFF
    # rfSettingsStruct.rx_FreqHopOn       = OFF
    # rfSettingsStruct.rx_HopPeriod       = 0
    # rfSettingsStruct.rx_IqInverted      = OFF
    # rfSettingsStruct.rx_RxContinuous    = ON

    rfSettingsStruct.tx_Modem           = 1
    rfSettingsStruct.tx_Power           = 2
    rfSettingsStruct.tx_Fdev            = 3
    rfSettingsStruct.tx_Bandwidth       = 4
    rfSettingsStruct.tx_SpreadingFactor = 5
    rfSettingsStruct.tx_CodeRate        = 6
    rfSettingsStruct.tx_PreambleLen     = 7
    rfSettingsStruct.tx_FixLen          = 8
    rfSettingsStruct.tx_CrcOn           = 9
    rfSettingsStruct.tx_FreqHopOn       = 10
    rfSettingsStruct.tx_HopPeriod       = 11
    rfSettingsStruct.tx_IqInverted      = 12
    rfSettingsStruct.tx_Timeout         = 13

    rfSettingsStruct.rx_Modem           = 14
    rfSettingsStruct.rx_Bandwidth       = 15
    rfSettingsStruct.rx_SpreadingFactor = 16
    rfSettingsStruct.rx_CodeRate        = 17
    rfSettingsStruct.rx_BandwidthAfc    = 18
    rfSettingsStruct.rx_PreambleLen     = 19
    rfSettingsStruct.rx_FixLen          = 20
    rfSettingsStruct.rx_PayloadLen      = 21
    rfSettingsStruct.rx_CrcOn           = 22
    rfSettingsStruct.rx_FreqHopOn       = 23
    rfSettingsStruct.rx_HopPeriod       = 24
    rfSettingsStruct.rx_IqInverted      = 25
    rfSettingsStruct.rx_RxContinuous    = 26

    return rfSettingsStruct


class Gateway:
    def __init__(self, portname):
        self.ser = self.openCOM(portname)
        print(f'Connected to gateway on {portname}')

        self.delimiter = b'\r'

    def openCOM(self, portname):
        return serial.Serial(
            port=portname,
            baudrate=921600,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS
        )

    def readLine(self):
        return self.ser.read_until(self.delimiter)

    def setNewRFsettings(self, rfSettings, broadcast=True):
        if broadcast:
            cmd = b'F' + bytes(rfSettings) + b'\r'
        else:
            cmd = b'G' + bytes(rfSettings) + b'\r'

        print(len(cmd))

        print(cmd)

        self.ser.write(cmd)

    # def setRFSettings(self, rfSettings):
    #     self.broadcastNewRFsettings(rfSettings)




