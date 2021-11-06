import asyncio
from serial_protocol import OutputProtocol, list_ports
import serial_asyncio
from cli import CliParser

# # rfSettings = RadioConfig.getDefaultLoRaConfig()


def setNewRFsettings(gateway, rfSettings, broadcast=True):
    if broadcast:
        cmd = b'F' + bytes(rfSettings) + b'\r'
    else:
        cmd = b'G' + bytes(rfSettings) + b'\r'

    print(cmd)
    gateway.write(cmd)


async def reader(port, baudrate):
    try:
        transport, protocol = await serial_asyncio.create_serial_connection(loop, OutputProtocol, port, baudrate=921600)
    except FileNotFoundError as e:
        list_ports()
        exit(-1)

    cli = CliParser()
    cli_routine = cli.get_cli(protocol)
    task = asyncio.create_task(cli_routine.interact())

    while True:
        await asyncio.sleep(0.3)

if __name__ == '__main__':
    filtered_ports = list_ports(
        debug=False, vendor_filter="STMicroelectronics")
    
    if len(filtered_ports) == 0:
        print("No STM device COM ports found")
        exit(-1)
    
    used_port = filtered_ports[0].device
    baudrate = 921600

    loop = asyncio.get_event_loop()
    loop.run_until_complete(reader(used_port, baudrate))
    loop.run_forever()
    loop.close()
