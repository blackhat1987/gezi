# Baidu RPC - A framework to host and access services throughout Baidu.
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved

# Author: The baidu-rpc authors (pbrpc@baidu.com)
# Date: 2015/05/11 17:45:10

class AuthContext(object):
    def __init__(self):
        self.is_service = False
        self.user = None
        self.group = None
        self.roles = None
        self.starter = None

class Authenticator(object):
    def GenerateCredential(self):
        '''
        Implement this method generate credential information which
        will be sent to `VerifyCredential' at server side. This method will be 
        called on client side.
        Return the generated credential information on success or None on
        failure
        '''
        raise NotImplementedError("Should have implemented this")

    def VerifyCredential(self, auth_str, client_addr):
        '''
        Implement this method to verify credential information
        `auth_str' from `client_addr'. You can fill credential
        context (result) into `*out_ctx' and later fetch this
        pointer from `Controller'.
        Return an instance of AuthContext on success or None on failure
        '''
        raise NotImplementedError("Should have implemented this")
