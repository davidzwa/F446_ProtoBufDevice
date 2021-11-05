"""Run a CLI to simulate dice throws."""

import random
import asyncio
import argparse

from cobs import cobs
from aioconsole import AsynchronousCli


class CliParser(object):
    serial_protocol = None

    async def gateway(self, reader, writer, faces):
        encoded = cobs.encode(bytearray(b'Test'))
        self.serial_protocol.write_buffer(encoded)

    def get_cli(self, new_serial_protocol):
        self.serial_protocol = new_serial_protocol
        parser = argparse.ArgumentParser(description="Control gateway device.")
        parser.add_argument(
            "--faces", "-f", metavar="N", type=int, default=6, help="Number of faces"
        )
        cli = AsynchronousCli(
            {"g": (self.gateway, parser)}, prog="gateway")

        return cli
