# Baidu RPC - A framework to host and access services throughout Baidu.
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved

# Author: The baidu-rpc authors (pbrpc@baidu.com)
# Date: 2015/04/09 21:28:47

import os
import sys
import imp
import multiprocessing 
import modulefinder
from google.protobuf import descriptor
from baidu.rpc import _cpp

_DEFAULT_NUM_WORKER_THREADS = 8

class ServerOptions:
    '''
    Options to start a server

    idle_timeout_sec:  idle connections(no data transmission) will be closed
                       after so many seconds.
    num_io_threads: number of I/O threads
    num_worker_threads: number of threads that user callbacks run on
    internal_port: Provide builtin services at this port instead of the one to Start(). default:-1
    '''
    def __init__(self):
        self.idle_timeout_sec = -1
        self.max_network_in = -1
        self.max_network_out = -1
        self.auth = None
        self.num_io_threads = multiprocessing.cpu_count()
        self.num_worker_threads = _DEFAULT_NUM_WORKER_THREADS
        self.internal_port = -1

def _GetDependencies(service):
    '''
    Return the serialized dependent FileDescriptors of the given service. 
    NOTE: the order of the returned list is undefined at present.
    '''
    # There are no interfaces to get dependent files in the Python module of
    # protobuf-2.4.1, so we list all dependent modules of the service class and
    # get the `DESCRIPTOR' variable (heavily depend on the implementation of
    # protobuf-2.4.1) as the workaround. TODO(chenzhangyi01): figure out whether
    # it's OK to the other version of protobuf
    deps = []
    finder = modulefinder.ModuleFinder()
    # Not use f.run_script because it regard file as PY_SOURCE, but the file might
    # be PY_COMPILED
    module_file = sys.modules[service.__module__].__file__
    dir, name = os.path.split(module_file)
    name, ext = os.path.splitext(name)
    stuff = ()
    if ext == '.pyc':
        source_file = "%s.py" % os.path.join(dir, name)
        if os.path.exists(source_file):
            # Analyse source file instead of compiled file because it might be
            # compiled again
            module_file = source_file
            stuff = ('.py', "r", imp.PY_SOURCE)
        else:
            stuff = ('.pyc', "r", imp.PY_COMPILED)
    else:
        stuff = (ext, "r", imp.PY_SOURCE)
    fp = open(module_file, 'r')
    finder.load_module(name, fp, module_file, stuff)
    fp.close()
    for mod_name, mod in finder.modules.iteritems():
        try:
            m = sys.modules[mod_name]
            if m.DESCRIPTOR.__class__ == descriptor.FileDescriptor:
                deps.append(m.DESCRIPTOR.serialized_pb)
        except (KeyError, ImportError, AttributeError):
            pass
    return deps
    
class Server(object):
    def __init__(self, num_worker_threads=8):
        self.__cpp_server = _cpp.ServerCreate()
        self.__pool = _cpp.ThreadPoolCreate()
        self.__started = False

    def AddService(self, service):
        '''
        Add the very service to server.
        Return True on success, False otherwise
        '''
        try:
            desc = service.DESCRIPTOR
            deps = _GetDependencies(service)
        except:
            return False
        return _cpp.ServerAddService(self.__cpp_server, service, desc.name,
                desc.file.serialized_pb, deps, self.__pool)

    def RemoveService(self, service):
        '''
        Remove the very service from Server
        Return True on success, False otherwise
        '''
        return _cpp.ServerRemoveService(self.__cpp_server, service)

    def Stop(self, closewait_ms=0):
        '''
         Stop accepting new connections and close existing ones after some time
         according to `closewait_ms'. Notice that this function changes behavior
         of Join() rather than doing all these stuff by itself.
         closewait_ms = 0 :
             close all connections to clients at once. Running requests may be
             lost if clients do not retry or have enough remaining time to retry.
         closewait_ms != 0 :
             Not close connections to clients, instead respond new requests with
             `EHOSTDOWN' error immediately. When clients see the error, they
             should skip this server and retry other servers. Doing this for at
             most closewait_ms milliseconds or indefinitely(closewait_ms < 0),
             then close left connections. Set closewait_ms to a reasonable value
             (longer than latency of most requests) so that most running requests
             are not lost. This is essential for SLA of production lines that
             adjust online servers frequently.
        '''
        _cpp.ServerStop(self.__cpp_server, closewait_ms)
        _cpp.ThreadPoolStop(self.__pool)
        

    def Join(self):
        ''' Wait until Server has already stopped'''
        _cpp.ServerJoin(self.__cpp_server)
        _cpp.ThreadPoolJoin(self.__pool)

    def Start(self, address, options=None):
        '''
        Start server which listen on `address' 
        Return True on success, False otherwise
        '''
        if self.__started:
            return False
        num_workers = _DEFAULT_NUM_WORKER_THREADS
        if options is not None:
            num_workers = options.num_worker_threads
        _cpp.ThreadPoolStart(self.__pool, num_workers)
        if _cpp.ServerStart(self.__cpp_server, str(address), options):
            self.__started = True
            return True
        else:
            _cpp.ThreadPoolStop(self.__pool)
            _cpp.ThreadPoolJoin(self.__pool)
            return False


    def SetVersion(self, version):
        _cpp.ServerSetVersion(self.__cpp_server, str(version))

