# Baidu RPC - A framework to host and access services throughout Baidu.
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved

# Author: The baidu-rpc authors (pbrpc@baidu.com)
# Date: 2015/05/12 16:16:06

from baidu.rpc import authenticator
import baassw

class GianoAuthenticator(authenticator.Authenticator):
    def __init__(self, gen=None, ver=None):
        '''
        Either `gen' or `ver' can be NULL (but not at the same time),
        in which case it can only verify/generate credential data
        Throws ValueError if both gen and ver are None
        '''
        if gen is None and ver is None:
            raise ValueError("Either gen or ver should be non-None")
        self.__generator = gen
        self.__verifier = ver
    def GenerateCredential(self):
        '''
        return the generated giano credential on success or None on failure
        '''
        if self.__generator is None:
            return None
        try:
            credential = baassw.string_p()
            self.__generator.GenerateCredential(credential.cast())
            return credential.value()
        except:
            return None
    
    def VerifyCredential(self, auth_str, client_addr):
        '''
        Verify giano credential generated at client side.
        '''
        if self.__verifier is None:
            return None
        ctx_verify = baassw.CredentialContext_p()
        if self.__verifier.Verify(auth_str, client_addr, ctx_verify.cast()) != 0:
            return None
        auth_ctx = authenticator.AuthContext()
        auth_ctx.is_service = ctx_verify.value().IsService()
        auth_ctx.user = ctx_verify.value().user()
        auth_ctx.group = ctx_verify.value().group()
        auth_ctx.roles = ctx_verify.value().roles()
        auth_ctx.starter = ctx_verify.value().starter()
        return auth_ctx
