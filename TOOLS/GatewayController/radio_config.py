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


def serialize(pb_msg, encode_cobs=True, debug=False):
    command_str = pb_msg.SerializeToString()
    l = len(command_str)
    buffer = bytearray()
    # Length byte
    buffer.extend(l.to_bytes(1, byteorder='little'))
    # Payload
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


class BootInfoCommand(object):
    @staticmethod
    def request_boot_info(debug=False):
        command = uart_messages_pb2.UartCommand()
        command.requestBootInfo.Request = True

        assert command.HasField('requestBootInfo') == True

        return serialize(command, debug=debug)


class TransmitCommands(object):
    @staticmethod
    def sendMulticastCommand(groupId=0, debug=False):
        command = uart_messages_pb2.UartCommand()
        command.transmitCommand.Payload = b'asd'
        command.transmitCommand.DeviceId = groupId
        command.transmitCommand.IsMulticast = True
        return serialize(command, debug=debug)

    @staticmethod
    def sendUnicastCommand(deviceId=0, debug=False):
        command = uart_messages_pb2.UartCommand()
        command.transmitCommand.Payload = b'asd'
        command.transmitCommand.DeviceId = deviceId
        command.transmitCommand.IsMulticast = False
        return serialize(command, debug=debug)


class RadioConfig(object):
    @staticmethod
    def setSpreadingFactorConfig(spreading_factor, debug=False):
        command = uart_messages_pb2.UartCommand()

        data = command.spreadingFactorConfig
        data.spreadingFactor = spreading_factor
        return serialize(command, debug=debug)

    @staticmethod
    def getTxConfig(debug=False):
        command = uart_messages_pb2.UartCommand()

        data = command.txConfig
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

        assert command.WhichOneof("Body") == "txConfig"
        assert command.HasField('rxConfig') == False
        assert command.HasField('txConfig') == True
        assert command.HasField('requestBootInfo') == False

        return serialize(command, debug=debug)

    @staticmethod
    def getRxConfig(debug=False):
        command = uart_messages_pb2.UartCommand()

        data = command.rxConfig
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

        assert command.WhichOneof("Body") == "rxConfig"
        assert command.HasField('rxConfig') == True
        assert command.HasField('txConfig') == False
        assert command.HasField('requestBootInfo') == False

        return serialize(command, debug=debug)
