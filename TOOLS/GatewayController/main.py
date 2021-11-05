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
    transport, protocol = await serial_asyncio.create_serial_connection(loop, OutputProtocol, port, baudrate=921600)

    cli = CliParser()
    cli_routine = cli.get_cli(protocol)
    task = asyncio.create_task(cli_routine.interact())

    while True:
        await asyncio.sleep(0.3)

if __name__ == '__main__':
    port = 'COM6'
    baudrate = 921600

    loop = asyncio.get_event_loop()
    
    try:
        loop.run_until_complete(reader(port,baudrate))
    except FileNotFoundError as e:
        list_ports()
        exit(-1)


    loop.run_forever()
    loop.close()
