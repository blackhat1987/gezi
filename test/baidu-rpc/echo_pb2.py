# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import service
from google.protobuf import service_reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)



DESCRIPTOR = descriptor.FileDescriptor(
  name='echo.proto',
  package='example',
  serialized_pb='\n\necho.proto\x12\x07\x65xample\"\x1e\n\x0b\x45\x63hoRequest\x12\x0f\n\x07message\x18\x01 \x02(\t\"\x1f\n\x0c\x45\x63hoResponse\x12\x0f\n\x07message\x18\x01 \x02(\t2B\n\x0b\x45\x63hoService\x12\x33\n\x04\x45\x63ho\x12\x14.example.EchoRequest\x1a\x15.example.EchoResponseB\x03\x90\x01\x01')




_ECHOREQUEST = descriptor.Descriptor(
  name='EchoRequest',
  full_name='example.EchoRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='message', full_name='example.EchoRequest.message', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
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
  extension_ranges=[],
  serialized_start=23,
  serialized_end=53,
)


_ECHORESPONSE = descriptor.Descriptor(
  name='EchoResponse',
  full_name='example.EchoResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='message', full_name='example.EchoResponse.message', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
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
  extension_ranges=[],
  serialized_start=55,
  serialized_end=86,
)

DESCRIPTOR.message_types_by_name['EchoRequest'] = _ECHOREQUEST
DESCRIPTOR.message_types_by_name['EchoResponse'] = _ECHORESPONSE

class EchoRequest(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _ECHOREQUEST
  
  # @@protoc_insertion_point(class_scope:example.EchoRequest)

class EchoResponse(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _ECHORESPONSE
  
  # @@protoc_insertion_point(class_scope:example.EchoResponse)


_ECHOSERVICE = descriptor.ServiceDescriptor(
  name='EchoService',
  full_name='example.EchoService',
  file=DESCRIPTOR,
  index=0,
  options=None,
  serialized_start=88,
  serialized_end=154,
  methods=[
  descriptor.MethodDescriptor(
    name='Echo',
    full_name='example.EchoService.Echo',
    index=0,
    containing_service=None,
    input_type=_ECHOREQUEST,
    output_type=_ECHORESPONSE,
    options=None,
  ),
])

class EchoService(service.Service):
  __metaclass__ = service_reflection.GeneratedServiceType
  DESCRIPTOR = _ECHOSERVICE
class EchoService_Stub(EchoService):
  __metaclass__ = service_reflection.GeneratedServiceStubType
  DESCRIPTOR = _ECHOSERVICE

# @@protoc_insertion_point(module_scope)
