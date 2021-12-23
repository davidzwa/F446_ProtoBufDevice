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




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x15\x64\x65vice_messages.proto\"H\n\x07Version\x12\r\n\x05Major\x18\x01 \x01(\r\x12\r\n\x05Minor\x18\x02 \x01(\r\x12\r\n\x05Patch\x18\x03 \x01(\r\x12\x10\n\x08Revision\x18\x04 \x01(\r\"1\n\x08\x44\x65viceId\x12\x0b\n\x03Id0\x18\x01 \x01(\r\x12\x0b\n\x03Id1\x18\x02 \x01(\r\x12\x0b\n\x03Id2\x18\x03 \x01(\r\"p\n\x0bLoraReceive\x12\x0c\n\x04Size\x18\x01 \x01(\r\x12\x0c\n\x04Rssi\x18\x02 \x01(\r\x12\x0b\n\x03Snr\x18\x03 \x01(\r\x12\x16\n\x0eSequenceNumber\x18\x04 \x01(\r\x12\x0f\n\x07Success\x18\x05 \x01(\x08\x12\x0f\n\x07Payload\x18\x06 \x01(\x0c\"f\n\x0b\x42ootMessage\x12#\n\x10\x44\x65viceIdentifier\x18\x01 \x01(\x0b\x32\t.DeviceId\x12!\n\x0f\x46irmwareVersion\x18\x02 \x01(\x0b\x32\x08.Version\x12\x0f\n\x07\x41ppName\x18\x03 \x01(\t\"$\n\nAckMessage\x12\x16\n\x0eSequenceNumber\x18\x01 \x01(\r\"\x8a\x01\n\x0cUartResponse\x12#\n\x0b\x62ootMessage\x18\x01 \x01(\x0b\x32\x0c.BootMessageH\x00\x12!\n\nackMessage\x18\x02 \x01(\x0b\x32\x0b.AckMessageH\x00\x12*\n\x12loraReceiveMessage\x18\x03 \x01(\x0b\x32\x0c.LoraReceiveH\x00\x42\x06\n\x04\x42ody\"M\n\x15SpreadingFactorConfig\x12\x19\n\x11spreadingFactorRx\x18\x01 \x01(\r\x12\x19\n\x11spreadingFactorTx\x18\x02 \x01(\r\"Q\n\x15SequenceRequestConfig\x12\x14\n\x0cMessageCount\x18\x01 \x01(\r\x12\x10\n\x08Interval\x18\x02 \x01(\r\x12\x10\n\x08\x44\x65viceId\x18\x03 \x01(\r\"\xe9\x02\n\x0bLoRaMessage\x12)\n\x07\x63ommand\x18\x01 \x01(\x0e\x32\x18.LoRaMessage.CommandType\x12\x16\n\x0eSequenceNumber\x18\x02 \x01(\r\x12\x37\n\x15spreadingFactorConfig\x18\x03 \x01(\x0b\x32\x16.SpreadingFactorConfigH\x00\x12\x37\n\x15sequenceRequestConfig\x18\x04 \x01(\x0b\x32\x16.SequenceRequestConfigH\x00\x12\x11\n\x07payload\x18\x05 \x01(\x0cH\x00\"\x89\x01\n\x0b\x43ommandType\x12\x11\n\rConfiguration\x10\x00\x12\r\n\tMultiCast\x10\x01\x12\x10\n\x0cMultiCastAck\x10\x02\x12\x0b\n\x07UniCast\x10\x03\x12\x0e\n\nUniCastAck\x10\x04\x12\x13\n\x0fSequenceRequest\x10\x05\x12\x14\n\x10SequenceResponse\x10\x06\x42\x06\n\x04\x42odyb\x06proto3')



_VERSION = DESCRIPTOR.message_types_by_name['Version']
_DEVICEID = DESCRIPTOR.message_types_by_name['DeviceId']
_LORARECEIVE = DESCRIPTOR.message_types_by_name['LoraReceive']
_BOOTMESSAGE = DESCRIPTOR.message_types_by_name['BootMessage']
_ACKMESSAGE = DESCRIPTOR.message_types_by_name['AckMessage']
_UARTRESPONSE = DESCRIPTOR.message_types_by_name['UartResponse']
_SPREADINGFACTORCONFIG = DESCRIPTOR.message_types_by_name['SpreadingFactorConfig']
_SEQUENCEREQUESTCONFIG = DESCRIPTOR.message_types_by_name['SequenceRequestConfig']
_LORAMESSAGE = DESCRIPTOR.message_types_by_name['LoRaMessage']
_LORAMESSAGE_COMMANDTYPE = _LORAMESSAGE.enum_types_by_name['CommandType']
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

UartResponse = _reflection.GeneratedProtocolMessageType('UartResponse', (_message.Message,), {
  'DESCRIPTOR' : _UARTRESPONSE,
  '__module__' : 'device_messages_pb2'
  # @@protoc_insertion_point(class_scope:UartResponse)
  })
_sym_db.RegisterMessage(UartResponse)

SpreadingFactorConfig = _reflection.GeneratedProtocolMessageType('SpreadingFactorConfig', (_message.Message,), {
  'DESCRIPTOR' : _SPREADINGFACTORCONFIG,
  '__module__' : 'device_messages_pb2'
  # @@protoc_insertion_point(class_scope:SpreadingFactorConfig)
  })
_sym_db.RegisterMessage(SpreadingFactorConfig)

SequenceRequestConfig = _reflection.GeneratedProtocolMessageType('SequenceRequestConfig', (_message.Message,), {
  'DESCRIPTOR' : _SEQUENCEREQUESTCONFIG,
  '__module__' : 'device_messages_pb2'
  # @@protoc_insertion_point(class_scope:SequenceRequestConfig)
  })
_sym_db.RegisterMessage(SequenceRequestConfig)

LoRaMessage = _reflection.GeneratedProtocolMessageType('LoRaMessage', (_message.Message,), {
  'DESCRIPTOR' : _LORAMESSAGE,
  '__module__' : 'device_messages_pb2'
  # @@protoc_insertion_point(class_scope:LoRaMessage)
  })
_sym_db.RegisterMessage(LoRaMessage)

if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _VERSION._serialized_start=25
  _VERSION._serialized_end=97
  _DEVICEID._serialized_start=99
  _DEVICEID._serialized_end=148
  _LORARECEIVE._serialized_start=150
  _LORARECEIVE._serialized_end=262
  _BOOTMESSAGE._serialized_start=264
  _BOOTMESSAGE._serialized_end=366
  _ACKMESSAGE._serialized_start=368
  _ACKMESSAGE._serialized_end=404
  _UARTRESPONSE._serialized_start=407
  _UARTRESPONSE._serialized_end=545
  _SPREADINGFACTORCONFIG._serialized_start=547
  _SPREADINGFACTORCONFIG._serialized_end=624
  _SEQUENCEREQUESTCONFIG._serialized_start=626
  _SEQUENCEREQUESTCONFIG._serialized_end=707
  _LORAMESSAGE._serialized_start=710
  _LORAMESSAGE._serialized_end=1071
  _LORAMESSAGE_COMMANDTYPE._serialized_start=926
  _LORAMESSAGE_COMMANDTYPE._serialized_end=1063
# @@protoc_insertion_point(module_scope)
