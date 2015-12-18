# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: echo.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import service as _service
from google.protobuf import service_reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='echo.proto',
  package='example',
  syntax='proto2',
  serialized_pb=_b('\n\necho.proto\x12\x07\x65xample\"\x1e\n\x0b\x45\x63hoRequest\x12\x0f\n\x07message\x18\x01 \x02(\t\"\x1f\n\x0c\x45\x63hoResponse\x12\x0f\n\x07message\x18\x01 \x02(\t2B\n\x0b\x45\x63hoService\x12\x33\n\x04\x45\x63ho\x12\x14.example.EchoRequest\x1a\x15.example.EchoResponseB\x03\x90\x01\x01')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_ECHOREQUEST = _descriptor.Descriptor(
  name='EchoRequest',
  full_name='example.EchoRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='message', full_name='example.EchoRequest.message', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=23,
  serialized_end=53,
)


_ECHORESPONSE = _descriptor.Descriptor(
  name='EchoResponse',
  full_name='example.EchoResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='message', full_name='example.EchoResponse.message', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=55,
  serialized_end=86,
)

DESCRIPTOR.message_types_by_name['EchoRequest'] = _ECHOREQUEST
DESCRIPTOR.message_types_by_name['EchoResponse'] = _ECHORESPONSE

EchoRequest = _reflection.GeneratedProtocolMessageType('EchoRequest', (_message.Message,), dict(
  DESCRIPTOR = _ECHOREQUEST,
  __module__ = 'echo_pb2'
  # @@protoc_insertion_point(class_scope:example.EchoRequest)
  ))
_sym_db.RegisterMessage(EchoRequest)

EchoResponse = _reflection.GeneratedProtocolMessageType('EchoResponse', (_message.Message,), dict(
  DESCRIPTOR = _ECHORESPONSE,
  __module__ = 'echo_pb2'
  # @@protoc_insertion_point(class_scope:example.EchoResponse)
  ))
_sym_db.RegisterMessage(EchoResponse)


DESCRIPTOR.has_options = True
DESCRIPTOR._options = _descriptor._ParseOptions(descriptor_pb2.FileOptions(), _b('\220\001\001'))

_ECHOSERVICE = _descriptor.ServiceDescriptor(
  name='EchoService',
  full_name='example.EchoService',
  file=DESCRIPTOR,
  index=0,
  options=None,
  serialized_start=88,
  serialized_end=154,
  methods=[
  _descriptor.MethodDescriptor(
    name='Echo',
    full_name='example.EchoService.Echo',
    index=0,
    containing_service=None,
    input_type=_ECHOREQUEST,
    output_type=_ECHORESPONSE,
    options=None,
  ),
])

EchoService = service_reflection.GeneratedServiceType('EchoService', (_service.Service,), dict(
  DESCRIPTOR = _ECHOSERVICE,
  __module__ = 'echo_pb2'
  ))

EchoService_Stub = service_reflection.GeneratedServiceStubType('EchoService_Stub', (EchoService,), dict(
  DESCRIPTOR = _ECHOSERVICE,
  __module__ = 'echo_pb2'
  ))


# @@protoc_insertion_point(module_scope)