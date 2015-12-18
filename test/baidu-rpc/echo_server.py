#!/usr/bin/env python2.7 

# Baidu RPC - A framework to host and access services throughout Baidu.
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved

'''
Please run setup.py first before you run this script

If you have any problem, contact us:
  Baidu Hi : group 1296497 
  Email    : pbrpc@baidu.com
  Wiki     : http://wiki.baidu.com/display/RPC

A server to receive EchoRequest and send back EchoResponse.
'''
import os
import sys
import time
import logging

''' Add extra library path '''
sys.path.append(os.path.abspath('./lib'))
sys.path.append(os.path.abspath(
        '../../../noah/giano-lib/release/baas-lib-c/python_interface'))

from baidu.rpc import server as rpc_server
from baidu.rpc.policy import giano_authenticator
import baassw
import gflags
import echo_pb2 as echo


''' Register gflags '''
FLAGS = gflags.FLAGS

gflags.DEFINE_integer('port', 8000, "TCP Port of this server")
gflags.DEFINE_integer('idle_timeout_s', -1, "Connection will be closed if there is"
                        " no read/write operations during the last"
                        " `idle_timeout_s'")
gflags.DEFINE_integer('logoff_ms', 2000, "Maximum duration of server's LOGOFF "
                      "state (waiting for client to close connection before "
                      "server stops)")
gflags.DEFINE_integer('num_io_threads', 8, 'Number of the I/O threads')
gflags.DEFINE_integer('num_worker_threads', 4, 'Number of the threads that user'
                      ' methods run on')
gflags.DEFINE_boolean('auth', False, 'Enable Giano authentication')

''' Configure logger '''
format = "%(levelname)s: %(asctime)s: %(filename)s:%(lineno)d * %(thread)d" \
            " %(message)s"
datefmt="%m-%d %H:%M:%S"
formatter = logging.Formatter(format, datefmt)

logger = logging.getLogger()
logger.setLevel(logging.INFO)
lh = logging.StreamHandler()
lh.setLevel(logging.INFO)
lh.setFormatter(formatter)
logger.addHandler(lh)


'''Implement EchoService'''
class EchoServiceImpl(echo.EchoService):
    def Echo(self, rpc_controller, request, done):
        response = echo.EchoResponse()
        response.message = request.message
        if done is not None:
            done(response)
        else:
            return response

def main(argv):
    '''Parse gflags'''
    try:
        argv = FLAGS(argv)
    except gflags.FlagsError as e:
        print '%s\\nUsage: %s ARGS\\n%s' % (e, sys.argv[0], FLAGS)
        sys.exit(-1)
    ''' Create a rpc server '''
    server = rpc_server.Server()
    '''Optional, will be shown on /version page'''
    server.SetVersion('echo_python_0.0.1-alpha')
    '''Instance of your implemented service'''
    service = EchoServiceImpl()
    '''Add the service into server'''
    if not server.AddService(service):
        sys.exit(-1)
    
    '''For more options see baidu.rpc.server'''
    options = rpc_server.ServerOptions()
    options.idle_timeout_sec = FLAGS.idle_timeout_s
    options.num_io_threads = FLAGS.num_io_threads
    options.num_worker_threads = FLAGS.num_worker_threads
    if FLAGS.auth:
        '''
        Setup for `GianoAuthenticator'
        Turn on giano mock (always pass authentication) for simplicity
        '''
        baassw.BAAS_Init()
        ver = baassw.ServerUtility.CreateCredentialVerifier()
        options.auth = giano_authenticator.GianoAuthenticator(ver=ver)

    '''Start the server'''
    if not server.Start('0.0.0.0:' + str(FLAGS.port), options):
        logger.critical('Fail to start EchoServer')
        sys.exit(-1)

    logger.info('EchoServer is serving on port=%d' % FLAGS.port)

    try:
        while True:
            time.sleep(1)
    except:
        server.Stop(FLAGS.logoff_ms)
        server.Join()

if __name__ == '__main__':
    main(sys.argv)
