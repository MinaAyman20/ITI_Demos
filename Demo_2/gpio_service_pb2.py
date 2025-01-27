# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: gpio_service.proto
# Protobuf Python Version: 4.25.1
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\x12gpio_service.proto\"\x1f\n\x10ReadStateRequest\x12\x0b\n\x03pin\x18\x01 \x01(\x05\"%\n\x11ReadStateResponse\x12\x10\n\x08response\x18\x01 \x01(\x08\".\n\x10SetOutputRequest\x12\x0b\n\x03pin\x18\x01 \x01(\x05\x12\r\n\x05state\x18\x02 \x01(\x08\"%\n\x11SetOutputResponse\x12\x10\n\x08response\x18\x01 \x01(\x08\"p\n\x13\x43onfigurePinRequest\x12\x0b\n\x03pin\x18\x01 \x01(\x05\x12*\n\x04mode\x18\x02 \x01(\x0e\x32\x1c.ConfigurePinRequest.PinMode\" \n\x07PinMode\x12\t\n\x05INPUT\x10\x00\x12\n\n\x06OUTPUT\x10\x01\"(\n\x14\x43onfigurePinResponse\x12\x10\n\x08response\x18\x01 \x01(\x08\x32\xb8\x01\n\x0bGPIOService\x12\x34\n\tReadState\x12\x11.ReadStateRequest\x1a\x12.ReadStateResponse\"\x00\x12\x34\n\tSetOutput\x12\x11.SetOutputRequest\x1a\x12.SetOutputResponse\"\x00\x12=\n\x0c\x43onfigurePin\x12\x14.ConfigurePinRequest\x1a\x15.ConfigurePinResponse\"\x00\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'gpio_service_pb2', _globals)
if _descriptor._USE_C_DESCRIPTORS == False:
  DESCRIPTOR._options = None
  _globals['_READSTATEREQUEST']._serialized_start=22
  _globals['_READSTATEREQUEST']._serialized_end=53
  _globals['_READSTATERESPONSE']._serialized_start=55
  _globals['_READSTATERESPONSE']._serialized_end=92
  _globals['_SETOUTPUTREQUEST']._serialized_start=94
  _globals['_SETOUTPUTREQUEST']._serialized_end=140
  _globals['_SETOUTPUTRESPONSE']._serialized_start=142
  _globals['_SETOUTPUTRESPONSE']._serialized_end=179
  _globals['_CONFIGUREPINREQUEST']._serialized_start=181
  _globals['_CONFIGUREPINREQUEST']._serialized_end=293
  _globals['_CONFIGUREPINREQUEST_PINMODE']._serialized_start=261
  _globals['_CONFIGUREPINREQUEST_PINMODE']._serialized_end=293
  _globals['_CONFIGUREPINRESPONSE']._serialized_start=295
  _globals['_CONFIGUREPINRESPONSE']._serialized_end=335
  _globals['_GPIOSERVICE']._serialized_start=338
  _globals['_GPIOSERVICE']._serialized_end=522
# @@protoc_insertion_point(module_scope)
