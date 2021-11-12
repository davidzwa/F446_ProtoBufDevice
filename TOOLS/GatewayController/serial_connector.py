from serial import Serial
from cobs import cobs
from protobuf import device_messages_pb2
from radio_config import BootInfoCommand
from data_store import data_store
from serial_asyncio import open_serial_connection
from utils.protocol import decode_message


class SerialConnection(object):
    def __init__(self, port, baudrate):
        self.serial_reader = None
        self.serial_writer = None
        self.start_bytes = bytes([0xFF])
        self.end_character = b'\0'
        self.port = port
        self.baudrate = baudrate

    def get_reader(self):
        if not self.serial_reader:
            raise ConnectionError("Cant get serial reader. Port not opened")
        return self.serial_reader

    async def open(self):
        if not self.serial_reader:
            reader, writer = await open_serial_connection(url=self.port, baudrate=self.baudrate)
            self.serial_reader = reader
            self.serial_writer = writer
            print(f"Connected on {self.port}")

    def is_open(self):
        return not not self.serial_reader

    def write_buffer(self, buffer):
        self.serial_writer.write(self.start_bytes)
        # print(len(buffer))
        self.serial_writer.write(bytes([len(buffer)]))
        # print('tx', buffer)
        self.serial_writer.write(buffer)
        self.serial_writer.write(self.end_character)

    async def process(self):
        reader = self.get_reader()
        await reader.readuntil(self.start_bytes)
        length_bytes = await reader.read(1)
        length = int.from_bytes(length_bytes, 'big')
        buffer = await reader.read(length)
        # print('rx', buffer)
        decode_message(buffer)

    def close(self):
        if self.serial:
            self.serial.close()


connections = dict()


def get_created_connection(port):
    return connections[port]


def get_connection(port, baudrate):
    if port not in connections.keys():
        connections[port] = SerialConnection(port, baudrate)

    return connections[port]
