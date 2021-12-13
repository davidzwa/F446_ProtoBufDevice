from data_store import data_store
from cobs import cobs
from protobuf import device_messages_pb2
from google.protobuf import message
import serial.tools.list_ports


def list_ports(debug=True, vendor_filter="STMicroelectronics"):
    ports = serial.tools.list_ports.comports()

    vendor_ports = list(
        filter(lambda comport: vendor_filter in comport.description, ports))

    if debug:
        for port, desc, hwid in sorted(vendor_ports):
            print("{}: {} [{}]".format(port, desc, hwid))

    return vendor_ports


def parse_firmware_version(spec):
    return f"{spec.Major}.{spec.Minor}.{spec.Patch}.{spec.Revision}"


def convert_device_id_string(spec):
    return str((spec.Id0 << 64) + (spec.Id1 << 32) + spec.Id2)


def parse_device_id(spec):
    return f"{hex(spec.Id0)}.{hex(spec.Id1)}.{hex(spec.Id2)}"


def print_lora_receive_message(lora_rx_message):
    print(f"LoRa RX (RSSI: {lora_rx_message.Rssi}) (SNR: {lora_rx_message.Snr})")

def print_ack_message(ack_message):
    print(f"ACK (sequence: {ack_message.SequenceNumber})")

def print_boot_message(boot_message):
    device_id = convert_device_id_string(boot_message.DeviceIdentifier)
    device = data_store.get_device(device_id, create_if_missing=True)
    if not device:
        print("error parsing boot message")
        return

    # print("App name: ", boot_message.AppName,
    #       "\nFirmware: ", parse_firmware_version(
    #           boot_message.FirmwareVersion),
    #       "\nDevice Id: ", hex(int(device_id)))
    print(f"Device heart beat {device['nickname']}")


def decode_message(data):
    try:
        decoded_data = cobs.decode(data)[1:-1]
        uart_packet = device_messages_pb2.UartResponse()
        uart_packet.ParseFromString(decoded_data)
        if uart_packet.HasField("bootMessage"):
            print_boot_message(uart_packet.bootMessage)
        elif uart_packet.HasField("ackMessage"):
            print_ack_message(uart_packet.ackMessage)
        elif uart_packet.HasField("loraReceive"):
            print_ack_message(uart_packet.loraReceive)
        else:
            print("packet not recognized")
    except cobs.DecodeError as e:
        print("! ", data)
        pass
    except message.DecodeError as e:
        print(e)
