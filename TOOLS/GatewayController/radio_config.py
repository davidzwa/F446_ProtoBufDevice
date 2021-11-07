from protobuf import uart_messages_pb2
from cobs import cobs

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


def print_buffer(prefix, buffer):
    print(prefix, buffer.hex())


class RadioConfig(object):
    @staticmethod
    def serialize(pb_msg, encode_cobs=True, debug=False):
        command_str = pb_msg.SerializeToString()
        l = len(command_str)
        buffer = bytearray()
        buffer.extend(l.to_bytes(1, byteorder='little'))
        buffer.extend(command_str)

        if encode_cobs:
            if debug:
                print_buffer("TX   ", buffer)
            encoded_buffer = cobs.encode(buffer)
            if debug:
                print_buffer("TXe", encoded_buffer)
            return encoded_buffer
        else:
            return buffer

    @staticmethod
    def getTxConfig():
        config = uart_messages_pb2.SetConfig()
        
        data = config.TxConfig
        data.Modem = MODEM_LORA
        data.Power = 14
        data.Fdev = 0
        data.Bandwidth = LORA_BANDWIDTH_125KHZ
        data.DataRate = 7
        data.CodeRate = LORA_CODINGRATE_6
        data.PreambleLen = 8
        data.FixLen = OFF
        data.CrcOn = OFF
        data.FreqHopOn = OFF
        data.HopPeriod = 0
        data.IqInverted = OFF
        data.Timeout = 0

        return config

    @staticmethod
    def getRxConfig():
        config = uart_messages_pb2.SetConfig()

        data = config.RxConfig
        data.Modem = MODEM_LORA
        data.Bandwidth = LORA_BANDWIDTH_125KHZ
        data.DataRate = 7
        data.CodeRate = LORA_CODINGRATE_6
        data.BandwidthAfc = 0
        data.PreambleLen = 8
        data.SymbTimeout = 5
        data.FixLen = OFF
        data.PayloadLen = 0
        data.CrcOn = OFF
        data.FreqHopOn = OFF
        data.HopPeriod = 0
        data.IqInverted = OFF
        data.RxContinuous = ON

        return config
