#!/usr/bin/env python2.7 

# Baidu RPC - A framework to host and access services throughout Baidu.
# Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved

import os
import sys
import subprocess

_PROTOBUF_PATH = '../../../../third-64/protobuf'
_PROTOC = os.path.join(_PROTOBUF_PATH, 'bin/protoc')
_PROTOBUF_INCLUDE_PATH = os.path.join(_PROTOBUF_PATH, 'include')
_PROTOCOL_PATH = '../protocol'

def generate_proto(source):
    """Invokes the Protocol Compiler to generate a _pb2.py from the given
    .proto file.  Does nothing if the output already exists and is newer than
    the input."""

    output = source.replace(".proto", "_pb2.py").replace("../protocol/", "")

    if not os.path.exists(source):
        print "Can't find required file: " + source
        sys.exit(-1)

    if (not os.path.exists(output) or
            (os.path.exists(source) and
                os.path.getmtime(source) > os.path.getmtime(output))):
                    print "Generating %s..." % output

                    protoc_command = [
                            _PROTOC, "-I../../protocol", "-I.", 
                            "-I" + _PROTOBUF_INCLUDE_PATH,
                            "--python_out=.", source
                    ]
                    if subprocess.call(protoc_command) != 0:
                        sys.exit(-1)

def copy_directory(src, dst):
    copy_command = ['cp', '-rf', src, dst]
    return subprocess.call(copy_command)

#Save PWD
saved_pwd = os.getcwd()
lib_path = os.path.join(saved_pwd, 'lib')
if not os.path.exists(lib_path):
    os.makedirs(lib_path)

#Switch working directory to the Python module location
os.chdir("../../python")

build_command = [sys.executable, 'setup.py', 'build']

if subprocess.call(build_command) != 0:
    sys.stderr.write('Fail to build the baidu-rpc Python module')
    sys.exit(-1)

if copy_directory('./google', lib_path) != 0:
    sys.stderr.write('Fail to copy protobuf library')
    sys.exit(-1)

if copy_directory(
        os.path.join('./build', 
            "lib.linux-x86_64-%d.%d" 
            % (sys.version_info.major, sys.version_info.minor),
            'baidu'), lib_path) != 0:

            sys.stderr.write('Fail to copy baidu-rpc')
            sys.exit(-1)

os.chdir(saved_pwd)
generate_proto('./echo.proto')

