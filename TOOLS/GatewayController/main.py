import asyncio
import serial
from utils.protocol import list_ports
from serial.serialutil import SerialException
from cli import CliParser
from data_store import data_store
from serial_connector import get_connection
from radio_config import TransmitCommands


async def cli_reader(port):
    cli = CliParser()
    cli_routine = cli.get_cli(port)
    await cli_routine.interact(stop=True)


async def serial_reader(connection):
    await connection.open()
    while True:
        try:
            await connection.process()
        except Exception as e:
            print("err", e)
            await connection.open()
            await asyncio.sleep(1)
        await asyncio.sleep(0.001)

async def unicast_worker(connection):
    while True:
        if connection.is_open():
            encoded_buffer = TransmitCommands.sendUnicastCommand(deviceId=12)
            connection.write_buffer(encoded_buffer)
        await asyncio.sleep(10)


async def main():
    data_store.load_json()

    filtered_ports = list_ports(
        debug=False, vendor_filter="STMicroelectronics")

    if len(filtered_ports) == 0:
        print("No STM device COM ports found")
        exit(-1)

    
    serial_port_name = filtered_ports[0].device
    connection = get_connection(serial_port_name, 921600)

    # Loop forever
    while True:
        f1 = loop.create_task(unicast_worker(connection))
        f2 = loop.create_task(serial_reader(connection))
        f3 = loop.create_task(cli_reader(serial_port_name))
        await asyncio.wait([f1, f2, f3])

if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
    loop.close()
