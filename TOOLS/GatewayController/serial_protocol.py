import asyncio as aio
import serial_asyncio
import serial.tools.list_ports
from cobs import cobs
from protobuf import device_messages_pb2
from data_store import data_store

def list_ports(debug=True, vendor_filter="STMicroelectronics"):
    ports = serial.tools.list_ports.comports()

    vendor_ports = list(
        filter(lambda comport: vendor_filter in comport.description, ports))

    if debug:
        for port, desc, hwid in sorted(vendor_ports):
            print("{}: {} [{}]".format(port, desc, hwid))

    return vendor_ports


async def create_connection(loop, port, baudrate):
    return await serial_asyncio.create_serial_connection(loop, OutputProtocol, port, baudrate)


def parse_firmware_version(spec):
    return f"{spec.Major}.{spec.Minor}.{spec.Patch}.{spec.Revision}"


def convert_device_id_string(spec):
    return str((spec.Id0 << 64) + (spec.Id1 << 32) + spec.Id2)

def parse_device_id(spec):
    return f"{hex(spec.Id0)}.{hex(spec.Id1)}.{hex(spec.Id2)}"


class OutputProtocol(aio.Protocol):
    end_character = b'\0'

    def connection_made(self, transport):
        self.transport = transport
        print('port opened', transport.serial.port)

    def write_buffer(self, buffer):
        self.transport.write(buffer)
        self.transport.write(self.end_character)

    def data_received(self, data):
        try:
            decoded_data = cobs.decode(data)[1:-1]
            # print('COBS decoded', decoded_data[0], decoded_data)
            uartResponse = device_messages_pb2.UartResponse()
            uartResponse.ParseFromString(decoded_data)
            if uartResponse.bootMessage:
                device_id = convert_device_id_string(
                    uartResponse.bootMessage.DeviceIdentifier)
                print("App name: ", uartResponse.bootMessage.AppName,
                      "\nFirmware: ", parse_firmware_version(
                          uartResponse.bootMessage.FirmwareVersion),
                      "\nDevice Id: ", hex(int(device_id)))

                device = data_store.get_device(device_id, create_if_missing=True)
                print(f"Device {device['nickname']}")

        except cobs.DecodeError:
            print("# ", data)
            pass

    def connection_lost(self, exc):
        print('serial - port closed')
        self.transport.loop.stop()

    def pause_writing(self):
        print('serial - pause writing')
        print(self.transport.get_write_buffer_size())

    def resume_writing(self):
        print(self.transport.get_write_buffer_size())
        print('serial - resume writing')
