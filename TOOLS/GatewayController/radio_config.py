import ctypes

ON = 1
OFF = 0

MODEM_FSK = 0
MODEM_LORA = 1

LORA_BANDWIDTH_125KHZ = 0
LORA_BANDWIDTH_250KHZ = 1
LORA_BANDWIDTH_500KHZ = 2

LORA_CODINGRATE_5 = 1
LORA_CODINGRATE_6 = 2
LORA_CODINGRATE_7 = 3
LORA_CODINGRATE_8 = 4


class RadioTXConfig(ctypes.Structure):
    _fields_ = (
        ('tx_Modem', ctypes.c_uint8),
        ('tx_Power', ctypes.c_int8),
        ('tx_Fdev', ctypes.c_uint32),
        ('tx_Bandwidth', ctypes.c_uint32),
        ('tx_DataRate', ctypes.c_uint32),
        ('tx_CodeRate', ctypes.c_uint8),
        ('tx_PreambleLen', ctypes.c_uint16),
        ('tx_FixLen', ctypes.c_uint8),
        ('tx_CrcOn', ctypes.c_uint8),
        ('tx_FreqHopOn', ctypes.c_uint8),
        ('tx_HopPeriod', ctypes.c_uint8),
        ('tx_IqInverted', ctypes.c_uint8),
        ('tx_Timeout', ctypes.c_uint32),
    )

    @staticmethod
    def getDefaultLoRaConfig():
        rfSettingsStruct = RadioTXConfig()

        rfSettingsStruct.tx_Modem = MODEM_LORA
        rfSettingsStruct.tx_Power = 14
        rfSettingsStruct.tx_Fdev = 0
        rfSettingsStruct.tx_Bandwidth = LORA_BANDWIDTH_125KHZ
        rfSettingsStruct.tx_DataRate = 7
        rfSettingsStruct.tx_CodeRate = LORA_CODINGRATE_6
        rfSettingsStruct.tx_PreambleLen = 8
        rfSettingsStruct.tx_FixLen = OFF
        rfSettingsStruct.tx_CrcOn = OFF
        rfSettingsStruct.tx_FreqHopOn = OFF
        rfSettingsStruct.tx_HopPeriod = 0
        rfSettingsStruct.tx_IqInverted = OFF
        rfSettingsStruct.tx_Timeout = 0

        return rfSettingsStruct


class RadioRXConfig(ctypes.Structure):
    _fields_ = (
        ('rx_Modem', ctypes.c_uint8),
        ('rx_Bandwidth', ctypes.c_uint32),
        ('rx_DataRate', ctypes.c_uint32),
        ('rx_CodeRate', ctypes.c_uint8),
        ('rx_BandwidthAfc', ctypes.c_uint32),
        ('rx_PreambleLen', ctypes.c_uint16),
        ('rx_SymbTimeout', ctypes.c_uint16),
        ('rx_FixLen', ctypes.c_uint8),
        ('rx_PayloadLen', ctypes.c_uint8),
        ('rx_CrcOn', ctypes.c_uint8),
        ('rx_FreqHopOn', ctypes.c_uint8),
        ('rx_HopPeriod', ctypes.c_uint8),
        ('rx_IqInverted', ctypes.c_uint8),
        ('rx_RxContinuous', ctypes.c_uint8)
    )

    @staticmethod
    def getDefaultLoRaConfig():
        rfSettingsStruct = RadioRXConfig()

        rfSettingsStruct.rx_Modem = MODEM_LORA
        rfSettingsStruct.rx_Bandwidth = LORA_BANDWIDTH_125KHZ
        rfSettingsStruct.rx_DataRate = 7
        rfSettingsStruct.rx_CodeRate = LORA_CODINGRATE_6
        rfSettingsStruct.rx_BandwidthAfc = 0
        rfSettingsStruct.rx_PreambleLen = 8
        rfSettingsStruct.rx_SymbTimeout = 5
        rfSettingsStruct.rx_FixLen = OFF
        rfSettingsStruct.rx_PayloadLen = 0
        rfSettingsStruct.rx_CrcOn = OFF
        rfSettingsStruct.rx_FreqHopOn = OFF
        rfSettingsStruct.rx_HopPeriod = 0
        rfSettingsStruct.rx_IqInverted = OFF
        rfSettingsStruct.rx_RxContinuous = ON

        return rfSettingsStruct
