# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: uart_messages.proto
"""Generated protocol buffer code."""
from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x13uart_messages.proto\"\xa6\x02\n\rRadioRxConfig\x12\x1b\n\x05Modem\x18\x01 \x01(\x0e\x32\x0c.RadioModems\x12\x11\n\tBandwidth\x18\x02 \x01(\r\x12\x10\n\x08\x44\x61taRate\x18\x03 \x01(\r\x12\x10\n\x08\x43odeRate\x18\x04 \x01(\r\x12\x14\n\x0c\x42\x61ndwidthAfc\x18\x05 \x01(\r\x12\x13\n\x0bPreambleLen\x18\x06 \x01(\r\x12\x13\n\x0bSymbTimeout\x18\x07 \x01(\r\x12\x0e\n\x06\x46ixLen\x18\x08 \x01(\x08\x12\x12\n\nPayloadLen\x18\t \x01(\r\x12\r\n\x05\x43rcOn\x18\n \x01(\x08\x12\x11\n\tFreqHopOn\x18\x0b \x01(\x08\x12\x11\n\tHopPeriod\x18\x0c \x01(\r\x12\x12\n\nIqInverted\x18\r \x01(\x08\x12\x14\n\x0cRxContinuous\x18\x0e \x01(\x08\"\xff\x01\n\rRadioTxConfig\x12\x1b\n\x05Modem\x18\x01 \x01(\x0e\x32\x0c.RadioModems\x12\r\n\x05Power\x18\x02 \x01(\r\x12\x0c\n\x04\x46\x64\x65v\x18\x03 \x01(\r\x12\x11\n\tBandwidth\x18\x04 \x01(\r\x12\x10\n\x08\x44\x61taRate\x18\x05 \x01(\r\x12\x10\n\x08\x43odeRate\x18\x06 \x01(\r\x12\x13\n\x0bPreambleLen\x18\x07 \x01(\r\x12\x0e\n\x06\x46ixLen\x18\x08 \x01(\x08\x12\r\n\x05\x43rcOn\x18\t \x01(\x08\x12\x11\n\tFreqHopOn\x18\n \x01(\x08\x12\x11\n\tHopPeriod\x18\x0b \x01(\r\x12\x12\n\nIqInverted\x18\x0c \x01(\x08\x12\x0f\n\x07Timeout\x18\r \x01(\r\"\xb1\x01\n\x0fTransmitCommand\x12\x13\n\x0bIsMulticast\x18\x01 \x01(\x08\x12\x10\n\x08\x44\x65viceId\x18\x02 \x01(\r\x12\x16\n\x0eSequenceNumber\x18\x03 \x01(\r\x12\x13\n\x06Period\x18\x04 \x01(\rH\x00\x88\x01\x01\x12\x1b\n\x0eMaxPacketCount\x18\x05 \x01(\rH\x01\x88\x01\x01\x12\x0f\n\x07Payload\x18\x06 \x01(\x0c\x42\t\n\x07_PeriodB\x11\n\x0f_MaxPacketCount\"\"\n\x0fRequestBootInfo\x12\x0f\n\x07Request\x18\x01 \x01(\x08\"I\n\x13\x44\x65viceConfiguration\x12\x18\n\x10\x45nableAlwaysSend\x18\x01 \x01(\x08\x12\x18\n\x10\x41lwaysSendPeriod\x18\x02 \x01(\r\"\xec\x01\n\x0bUartCommand\x12\"\n\x08rxConfig\x18\x01 \x01(\x0b\x32\x0e.RadioRxConfigH\x00\x12\"\n\x08txConfig\x18\x02 \x01(\x0b\x32\x0e.RadioTxConfigH\x00\x12\x33\n\x13\x64\x65viceConfiguration\x18\x03 \x01(\x0b\x32\x14.DeviceConfigurationH\x00\x12+\n\x0ftransmitCommand\x18\x04 \x01(\x0b\x32\x10.TransmitCommandH\x00\x12+\n\x0frequestBootInfo\x18\x05 \x01(\x0b\x32\x10.RequestBootInfoH\x00\x42\x06\n\x04\x42ody*,\n\x0bRadioModems\x12\r\n\tMODEM_FSK\x10\x00\x12\x0e\n\nMODEM_LORA\x10\x01\x62\x06proto3')

_RADIOMODEMS = DESCRIPTOR.enum_types_by_name['RadioModems']
RadioModems = enum_type_wrapper.EnumTypeWrapper(_RADIOMODEMS)
MODEM_FSK = 0
MODEM_LORA = 1


_RADIORXCONFIG = DESCRIPTOR.message_types_by_name['RadioRxConfig']
_RADIOTXCONFIG = DESCRIPTOR.message_types_by_name['RadioTxConfig']
_TRANSMITCOMMAND = DESCRIPTOR.message_types_by_name['TransmitCommand']
_REQUESTBOOTINFO = DESCRIPTOR.message_types_by_name['RequestBootInfo']
_DEVICECONFIGURATION = DESCRIPTOR.message_types_by_name['DeviceConfiguration']
_UARTCOMMAND = DESCRIPTOR.message_types_by_name['UartCommand']
RadioRxConfig = _reflection.GeneratedProtocolMessageType('RadioRxConfig', (_message.Message,), {
  'DESCRIPTOR' : _RADIORXCONFIG,
  '__module__' : 'uart_messages_pb2'
  # @@protoc_insertion_point(class_scope:RadioRxConfig)
  })
_sym_db.RegisterMessage(RadioRxConfig)

RadioTxConfig = _reflection.GeneratedProtocolMessageType('RadioTxConfig', (_message.Message,), {
  'DESCRIPTOR' : _RADIOTXCONFIG,
  '__module__' : 'uart_messages_pb2'
  # @@protoc_insertion_point(class_scope:RadioTxConfig)
  })
_sym_db.RegisterMessage(RadioTxConfig)

TransmitCommand = _reflection.GeneratedProtocolMessageType('TransmitCommand', (_message.Message,), {
  'DESCRIPTOR' : _TRANSMITCOMMAND,
  '__module__' : 'uart_messages_pb2'
  # @@protoc_insertion_point(class_scope:TransmitCommand)
  })
_sym_db.RegisterMessage(TransmitCommand)

RequestBootInfo = _reflection.GeneratedProtocolMessageType('RequestBootInfo', (_message.Message,), {
  'DESCRIPTOR' : _REQUESTBOOTINFO,
  '__module__' : 'uart_messages_pb2'
  # @@protoc_insertion_point(class_scope:RequestBootInfo)
  })
_sym_db.RegisterMessage(RequestBootInfo)

DeviceConfiguration = _reflection.GeneratedProtocolMessageType('DeviceConfiguration', (_message.Message,), {
  'DESCRIPTOR' : _DEVICECONFIGURATION,
  '__module__' : 'uart_messages_pb2'
  # @@protoc_insertion_point(class_scope:DeviceConfiguration)
  })
_sym_db.RegisterMessage(DeviceConfiguration)

UartCommand = _reflection.GeneratedProtocolMessageType('UartCommand', (_message.Message,), {
  'DESCRIPTOR' : _UARTCOMMAND,
  '__module__' : 'uart_messages_pb2'
  # @@protoc_insertion_point(class_scope:UartCommand)
  })
_sym_db.RegisterMessage(UartCommand)

if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _RADIOMODEMS._serialized_start=1108
  _RADIOMODEMS._serialized_end=1152
  _RADIORXCONFIG._serialized_start=24
  _RADIORXCONFIG._serialized_end=318
  _RADIOTXCONFIG._serialized_start=321
  _RADIOTXCONFIG._serialized_end=576
  _TRANSMITCOMMAND._serialized_start=579
  _TRANSMITCOMMAND._serialized_end=756
  _REQUESTBOOTINFO._serialized_start=758
  _REQUESTBOOTINFO._serialized_end=792
  _DEVICECONFIGURATION._serialized_start=794
  _DEVICECONFIGURATION._serialized_end=867
  _UARTCOMMAND._serialized_start=870
  _UARTCOMMAND._serialized_end=1106
# @@protoc_insertion_point(module_scope)
