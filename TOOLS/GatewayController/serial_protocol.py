import asyncio as aio
import serial_asyncio
import serial.tools.list_ports
from cobs import cobs


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
            print('COBS decoded', cobs.decode(data))
        except cobs.DecodeError:
            print("# ", data.decode())
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
