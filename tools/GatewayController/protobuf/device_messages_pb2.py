# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: device_messages.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x15\x64\x65vice_messages.proto\"H\n\x07Version\x12\r\n\x05Major\x18\x01 \x01(\r\x12\r\n\x05Minor\x18\x02 \x01(\r\x12\r\n\x05Patch\x18\x03 \x01(\r\x12\x10\n\x08Revision\x18\x04 \x01(\r\"1\n\x08\x44\x65viceId\x12\x0b\n\x03Id0\x18\x01 \x01(\r\x12\x0b\n\x03Id1\x18\x02 \x01(\r\x12\x0b\n\x03Id2\x18\x03 \x01(\r\"\xae\x01\n\x0bLoraReceive\x12\x0c\n\x04Size\x18\x01 \x01(\r\x12\x0c\n\x04Rssi\x18\x02 \x01(\x05\x12\x0b\n\x03Snr\x18\x03 \x01(\x05\x12\x16\n\x0eSequenceNumber\x18\x04 \x01(\r\x12\"\n\x15IsMeasurementFragment\x18\x05 \x01(\x08H\x00\x88\x01\x01\x12\x0f\n\x07Success\x18\x06 \x01(\x08\x12\x0f\n\x07Payload\x18\x07 \x01(\x0c\x42\x18\n\x16_IsMeasurementFragment\"\x9e\x01\n\x0b\x42ootMessage\x12#\n\x10\x44\x65viceIdentifier\x18\x01 \x01(\x0b\x32\t.DeviceId\x12!\n\x0f\x46irmwareVersion\x18\x02 \x01(\x0b\x32\x08.Version\x12\x0f\n\x07\x41ppName\x18\x03 \x01(\t\x12\x18\n\x10MeasurementCount\x18\x04 \x01(\r\x12\x1c\n\x14MeasurementsDisabled\x18\x05 \x01(\x08\"$\n\nAckMessage\x12\x16\n\x0eSequenceNumber\x18\x01 \x01(\r\"\x1f\n\x0c\x44\x65\x62ugMessage\x12\x0f\n\x07payload\x18\x01 \x01(\x0c\"\xb1\x01\n\x0cUartResponse\x12#\n\x0b\x62ootMessage\x18\x01 \x01(\x0b\x32\x0c.BootMessageH\x00\x12!\n\nackMessage\x18\x02 \x01(\x0b\x32\x0b.AckMessageH\x00\x12*\n\x12loraReceiveMessage\x18\x03 \x01(\x0b\x32\x0c.LoraReceiveH\x00\x12%\n\x0c\x64\x65\x62ugMessage\x18\x04 \x01(\x0b\x32\r.DebugMessageH\x00\x42\x06\n\x04\x42odyb\x06proto3')



_VERSION = DESCRIPTOR.message_types_by_name['Version']
_DEVICEID = DESCRIPTOR.message_types_by_name['DeviceId']
_LORARECEIVE = DESCRIPTOR.message_types_by_name['LoraReceive']
_BOOTMESSAGE = DESCRIPTOR.message_types_by_name['BootMessage']
_ACKMESSAGE = DESCRIPTOR.message_types_by_name['AckMessage']
_DEBUGMESSAGE = DESCRIPTOR.message_types_by_name['DebugMessage']
_UARTRESPONSE = DESCRIPTOR.message_types_by_name['UartResponse']
Version = _reflection.GeneratedProtocolMessageType('Version', (_message.Message,), {
  'DESCRIPTOR' : _VERSION,
  '__module__' : 'device_messages_pb2'
  # @@protoc_insertion_point(class_scope:Version)
  })
_sym_db.RegisterMessage(Version)

DeviceId = _reflection.GeneratedProtocolMessageType('DeviceId', (_message.Message,), {
  'DESCRIPTOR' : _DEVICEID,
  '__module__' : 'device_messages_pb2'
  # @@protoc_insertion_point(class_scope:DeviceId)
  })
_sym_db.RegisterMessage(DeviceId)

LoraReceive = _reflection.GeneratedProtocolMessageType('LoraReceive', (_message.Message,), {
  'DESCRIPTOR' : _LORARECEIVE,
  '__module__' : 'device_messages_pb2'
  # @@protoc_insertion_point(class_scope:LoraReceive)
  })
_sym_db.RegisterMessage(LoraReceive)

BootMessage = _reflection.GeneratedProtocolMessageType('BootMessage', (_message.Message,), {
  'DESCRIPTOR' : _BOOTMESSAGE,
  '__module__' : 'device_messages_pb2'
  # @@protoc_insertion_point(class_scope:BootMessage)
  })
_sym_db.RegisterMessage(BootMessage)

AckMessage = _reflection.GeneratedProtocolMessageType('AckMessage', (_message.Message,), {
  'DESCRIPTOR' : _ACKMESSAGE,
  '__module__' : 'device_messages_pb2'
  # @@protoc_insertion_point(class_scope:AckMessage)
  })
_sym_db.RegisterMessage(AckMessage)

DebugMessage = _reflection.GeneratedProtocolMessageType('DebugMessage', (_message.Message,), {
  'DESCRIPTOR' : _DEBUGMESSAGE,
  '__module__' : 'device_messages_pb2'
  # @@protoc_insertion_point(class_scope:DebugMessage)
  })
_sym_db.RegisterMessage(DebugMessage)

UartResponse = _reflection.GeneratedProtocolMessageType('UartResponse', (_message.Message,), {
  'DESCRIPTOR' : _UARTRESPONSE,
  '__module__' : 'device_messages_pb2'
  # @@protoc_insertion_point(class_scope:UartResponse)
  })
_sym_db.RegisterMessage(UartResponse)

if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _VERSION._serialized_start=25
  _VERSION._serialized_end=97
  _DEVICEID._serialized_start=99
  _DEVICEID._serialized_end=148
  _LORARECEIVE._serialized_start=151
  _LORARECEIVE._serialized_end=325
  _BOOTMESSAGE._serialized_start=328
  _BOOTMESSAGE._serialized_end=486
  _ACKMESSAGE._serialized_start=488
  _ACKMESSAGE._serialized_end=524
  _DEBUGMESSAGE._serialized_start=526
  _DEBUGMESSAGE._serialized_end=557
  _UARTRESPONSE._serialized_start=560
  _UARTRESPONSE._serialized_end=737
# @@protoc_insertion_point(module_scope)
