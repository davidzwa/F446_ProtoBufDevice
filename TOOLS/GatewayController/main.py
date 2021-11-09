import asyncio
from serial_protocol import list_ports, create_connection
from serial.serialutil import SerialException
from cli import CliParser
from data_store import data_store


async def reader(port, baudrate):
    try:
        transport, protocol = await create_connection(loop, port, baudrate)
    except SerialException as e:
        print("Port closed")
    except FileNotFoundError as e:
        print("Port not found. Devices:")
        list_ports()
        exit(-1)

    cli = CliParser()
    cli_routine = cli.get_cli(protocol)
    task = asyncio.create_task(cli_routine.interact())

    while True:
        await asyncio.sleep(0.3)

if __name__ == '__main__':
    data_store.load_json()

    filtered_ports = list_ports(
        debug=False, vendor_filter="STMicroelectronics")

    if len(filtered_ports) == 0:
        print("No STM device COM ports found")
        exit(-1)

    used_port = filtered_ports[0].device
    baudrate = 921600

    loop = asyncio.get_event_loop()
    try:
        loop.run_until_complete(reader(used_port, baudrate))
    except RuntimeError as e:
        print("Error occurred breaking")
        exit(0)
    loop.run_forever()
    loop.close()
