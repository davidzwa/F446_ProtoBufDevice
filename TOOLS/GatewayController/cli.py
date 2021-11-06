"""Run a CLI to simulate dice throws."""

import random
import asyncio
import argparse
import time

from cobs import cobs
from aioconsole import AsynchronousCli
from serial_protocol import list_ports
from radio_config import RadioRXConfig, RadioTXConfig


class CliParser(object):
    serial_protocol = None

    def __send(self, buffer):
        self.serial_protocol.write_buffer(buffer)

    async def gateway(self, reader, writer, port, device):
        print(port, device)
        encoded = cobs.encode(bytearray(b'Test'))
        self.__send(encoded)

    async def transmit(self, reader, writer):
        encoded = cobs.encode(bytearray(b'Test2'))
        self.__send(encoded)

    async def list_serial_ports(self, reader, writer):
        list_ports()

    async def send_radio_config(self, reader, writer):
        rx_settings = RadioRXConfig.getDefaultLoRaConfig()
        print(rx_settings)
        byte_data = bytes(rx_settings)
        encoded_data = cobs.encode(byte_data)
        print(
            f"Configuring RX settings ({len(byte_data)} bytes, {len(encoded_data)} encoded)")

        self.__send(encoded_data)

        # time.sleep(1)
        # print("\nConfiguring TX settings")
        # radioTransmitSettings = RadioTXConfig.getDefaultLoRaConfig()
        # self.__send(cobs.encode(radioTransmitSettings))

    async def switch_serial_port(self, reader, writer, port, device):
        print("switching")

    def get_parser(self):
        return argparse.ArgumentParser(description="Control gateway device.")

    def get_cli(self, new_serial_protocol):
        parser = self.get_parser()
        self.serial_protocol = new_serial_protocol
        parser = argparse.ArgumentParser(description="Control gateway device.")
        parser.add_argument(
            "--port", "-p", metavar="N", type=int, default=4, help="Port"
        )
        parser.add_argument(
            "--device", "-d", metavar="N", type=int, default=0, help="Device ID"
        )

        cli = AsynchronousCli(
            {
                "g": (self.gateway, parser),
                "t": (self.transmit, self.get_parser()),
                "l": (self.list_serial_ports, self.get_parser()),
                "R": (self.send_radio_config, self.get_parser()),
                "p": (self.switch_serial_port, parser)
            },
            prog="gateway"
        )

        return cli
