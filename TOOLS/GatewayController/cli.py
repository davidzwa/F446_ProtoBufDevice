"""Run a CLI to process commands for the gateway end device."""

import random
import asyncio
import argparse
import time

from cobs import cobs
from aioconsole import AsynchronousCli
from utils.protocol import list_ports
from radio_config import RadioConfig, TransmitCommands, BootInfoCommand
from protobuf import uart_messages_pb2
from serial_connector import get_created_connection


class CliParser(object):
    serial_protocol = None

    def __send(self, buffer):
        self.serial_protocol.write_buffer(buffer)

    async def list_serial_ports(self, reader, writer):
        list_ports()

    async def send_spreading_factor(self, reader, writer, sf):
        if sf < 7 or sf > 12:
            print(f"Spreading factor {sf} was not in range (7-12)")
            return

        # TODO not implemented
        # encoded_buffer = RadioConfig.setSpreadingFactorConfig(sf)
        # self.__send(encoded_buffer)

    async def request_boot_info(self, reader, writer):
        encoded_buffer = BootInfoCommand.request_boot_info()
        self.__send(encoded_buffer)

    async def send_radio_tx_config(self, reader, writer):
        encoded_buffer = RadioConfig.getTxConfig()
        self.__send(encoded_buffer)

    async def send_radio_rx_config(self, reader, writer):
        encoded_buffer = RadioConfig.getRxConfig()
        self.__send(encoded_buffer)
    
    async def send_periodic_config(self, reader, writer, period):
        encoded_buffer = TransmitCommands.sendUnicastCommand(
            deviceId=12, debug=False, period=period, max_packet_count=10)
        self.__send(encoded_buffer)

    async def send_multicast_command(self, reader, writer):
        encoded_buffer = TransmitCommands.sendMulticastCommand(groupId=12)
        self.__send(encoded_buffer)

    async def send_unicast_command(self, reader, writer):
        encoded_buffer = TransmitCommands.sendUnicastCommand(deviceId=12)
        self.__send(encoded_buffer)

    async def switch_serial_port(self, reader, writer, com):
        print(f"switching to port {com}")

    def get_parser(self):
        return argparse.ArgumentParser(description="Control gateway device.")

    def get_cli(self, serial_port_name):
        parser = self.get_parser()
        self.serial_protocol = get_created_connection(serial_port_name)
        parser = argparse.ArgumentParser(description="Control gateway device.")
        parser.add_argument(
            "--port", "-p", metavar="N", type=int, default=4, help="Port"
        )
        parser.add_argument(
            "--device", "-d", metavar="N", type=int, default=0, help="Device ID"
        )

        sf_parser = argparse.ArgumentParser(
            description="Get spreading factor.")
        sf_parser.add_argument("sf", type=int)

        periodic_tx_parser = argparse.ArgumentParser(
            description="Set device periodic tranmission")
        periodic_tx_parser.add_argument("period", type=int)
        # periodic_tx_parser.add_argument("max_period_count", type=int)

        port_parser = argparse.ArgumentParser(
            description="Change serial port.")
        port_parser.add_argument("com", type=int)

        cli = AsynchronousCli(
            {
                "l": (self.list_serial_ports, self.get_parser()),
                "port": (self.switch_serial_port, port_parser),
                "boot": (self.request_boot_info, self.get_parser()),
                "sf": (self.send_spreading_factor, sf_parser),
                "P": (self.send_periodic_config, periodic_tx_parser),
                "T": (self.send_radio_tx_config, self.get_parser()),
                "R": (self.send_radio_rx_config, self.get_parser()),
                "M": (self.send_multicast_command, self.get_parser()),
                "U": (self.send_unicast_command, self.get_parser()),
            },
            prog="gateway"
        )

        return cli
