import asyncio as aio
import serial_asyncio
import serial.tools.list_ports
from cobs import cobs

def list_ports(self):
    ports = serial.tools.list_ports.comports()

    for port, desc, hwid in sorted(ports):
        print("{}: {} [{}]".format(port, desc, hwid))

    return ports

class OutputProtocol(aio.Protocol):
    end_character = b'\0\n'

    def connection_made(self, transport):
        self.transport = transport
        print('port opened', transport.serial.port)
    
    def write_buffer(self, buffer):
        self.transport.write(buffer)
        self.transport.write(self.end_character)

    def data_received(self, data):
        print('RX', data)
        # print(cobs.decode(data))
        # if (data[0] == '\x0c'):
            
        # else:
        #     print('RX', str(data))

    def connection_lost(self, exc):
        print('serial - port closed')
        self.transport.loop.stop()

    def pause_writing(self):
        print('serial - pause writing')
        print(self.transport.get_write_buffer_size())

    def resume_writing(self):
        print(self.transport.get_write_buffer_size())
        print('serial - resume writing')
