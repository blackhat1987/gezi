# Baidu RPC - A framework to host and access services throughout Baidu.
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved

# Author: The baidu-rpc authors (pbrpc@baidu.com)
# Date: 2015/04/08 16:53:10

'''Tunnel between C++ and Python'''

from baidu.rpc import _cpp
from baidu.rpc import errno_pb2 as _errno

class Message(object):
    def __init__(self):
        self._request_buf = None
        self._response = None
        self._cntl = None
        self._closure = None
        self._method_index = -1

class Closure(object):
    def __init__(self, message):
        self.__message = message
        self.__called = False

    def __call__(self, response):
        if self.__called:
            return
        self.__called = True
        if response is not None:
            try:
                self.__message._response = response.SerializeToString()
            except Exception as e:
                self.__message._cntl.SetFailedWithErrorCode(
                        _errno.EINTERNAL, str(e))
        _cpp.RunClosure(self.__message._closure)

def CallMethodImpl(service, message):
    service_desc = service.DESCRIPTOR
    method = service_desc.methods[message._method_index]
    request = service.GetRequestClass(method) ()
    request.ParseFromString(message._request_buf)
    done = Closure(message)
    try:
        service.CallMethod(method, message._cntl, request, done)
    except Exception as e:
        message._cntl.SetFailedWithErrorCode(_errno.EINTERNAL,
                                             str(e))
        done(None)
