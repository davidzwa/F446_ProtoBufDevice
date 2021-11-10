import asyncio
from serial_protocol import list_ports, create_connection
from serial.serialutil import SerialException
from cli import CliParser
from data_store import data_store


async def reader(port, baudrate):
    try:
        transport, serial_protocol = await create_connection(loop, port, baudrate)
    except SerialException as e:
        print("Port closed")
    except FileNotFoundError as e:
        print("Port not found. Devices:")
        list_ports()
        exit(-1)

    cli = CliParser()
    cli_routine = cli.get_cli(serial_protocol)
    
    await cli_routine.interact(stop=True)

async def main():
    # Loop forever
    while True:
        f1 = loop.create_task(reader(used_port, baudrate))
        await asyncio.wait([f1])
        
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
    loop.run_until_complete(main())
    loop.close()
