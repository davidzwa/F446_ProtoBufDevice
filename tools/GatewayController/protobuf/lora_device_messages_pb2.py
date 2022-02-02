# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: lora_device_messages.proto
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from shared import lora_config_pb2 as shared_dot_lora__config__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x1alora_device_messages.proto\x1a\x18shared/lora_config.proto\"\xab\x03\n\x0bLoRaMessage\x12)\n\x07\x63ommand\x18\x01 \x01(\x0e\x32\x18.LoRaMessage.CommandType\x12\x16\n\x0eSequenceNumber\x18\x02 \x01(\r\x12\x37\n\x15spreadingFactorConfig\x18\x03 \x01(\x0b\x32\x16.SpreadingFactorConfigH\x00\x12\x37\n\x15sequenceRequestConfig\x18\x04 \x01(\x0b\x32\x16.SequenceRequestConfigH\x00\x12\x11\n\x07payload\x18\x05 \x01(\x0cH\x00\"\xcb\x01\n\x0b\x43ommandType\x12\x11\n\rConfiguration\x10\x00\x12\r\n\tMultiCast\x10\x01\x12\x10\n\x0cMultiCastAck\x10\x02\x12\x0b\n\x07UniCast\x10\x03\x12\x0e\n\nUniCastAck\x10\x04\x12\x1c\n\x18MeasurementStreamRequest\x10\x05\x12\"\n\x1eMeasurementStreamFragmentReply\x10\x06\x12\x13\n\x0fSequenceRequest\x10\x07\x12\x14\n\x10SequenceResponse\x10\x08\x42\x06\n\x04\x42odyb\x06proto3')



_LORAMESSAGE = DESCRIPTOR.message_types_by_name['LoRaMessage']
_LORAMESSAGE_COMMANDTYPE = _LORAMESSAGE.enum_types_by_name['CommandType']
LoRaMessage = _reflection.GeneratedProtocolMessageType('LoRaMessage', (_message.Message,), {
  'DESCRIPTOR' : _LORAMESSAGE,
  '__module__' : 'lora_device_messages_pb2'
  # @@protoc_insertion_point(class_scope:LoRaMessage)
  })
_sym_db.RegisterMessage(LoRaMessage)

if _descriptor._USE_C_DESCRIPTORS == False:

  DESCRIPTOR._options = None
  _LORAMESSAGE._serialized_start=57
  _LORAMESSAGE._serialized_end=484
  _LORAMESSAGE_COMMANDTYPE._serialized_start=273
  _LORAMESSAGE_COMMANDTYPE._serialized_end=476
# @@protoc_insertion_point(module_scope)