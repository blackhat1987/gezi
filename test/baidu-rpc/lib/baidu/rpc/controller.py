# Baidu RPC - A framework to host and access services throughout Baidu.
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved

# Author: The baidu-rpc authors (pbrpc@baidu.com)
# Date: 2015/04/03 15:16:15

from google.protobuf import service as _service
from baidu.rpc import _cpp

class Controller(_service.RpcController):
    def __init__(self):
        self.log_id = 0
        self.request_attachment = None
        self.response_attachment = None
        self.remote_side = None
        self._cpp_cntl = None
    
    """
    The primary purpose of the controller is to provide a way to manipulate
    settings specific to the RPC implementation and to find out about RPC-level
    errors. The methods provided by the RpcController interface are intended
    to be a "least common denominator" set of features which we expect all
    implementations to support.  Specific implementations may provide more
    advanced features (e.g. deadline propagation).
    """
    # Client-side methods below (Not supported now)

    # Server-side methods below

    def SetFailed(self, reason):
        """Sets a failure reason.

        Causes Failed() to return true on the client side.  "reason" will be
        incorporated into the message returned by ErrorText().  If you find
        you need to return machine-readable information about failures, you
        should incorporate it into your response protocol buffer and should
        NOT call SetFailed().
        """
        return _cpp.ControllerSetFailed(self._cpp_cntl, reason)

    def SetFailedWithErrorCode(self, error_code, reason=None):
        return _cpp.ControllerSetFailedWithErrorCode(self._cpp_cntl,
                         error_code, str(reason) if reason is None else None)

    def IsCanceled(self):
        """Checks if the client cancelled the RPC.

        If true, indicates that the client canceled the RPC, so the server may
        as well give up on replying to it.  The server should still call the
        final "done" callback.
        """
        raise _cpp.ControllerIsCanceled(self._cpp_cntl)
