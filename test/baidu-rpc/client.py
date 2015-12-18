#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   client.py
#        \author   chenghuige  
#          \date   2015-12-17 14:59:52.323369
#   \Description  
# ==============================================================================

import json
import urllib2

'''����request json��'''
data = { "message" : "hello world" }
request_json = json.dumps(data)
'''����HTTP����'''
req = urllib2.Request("http://127.0.0.1:8000/EchoService/Echo")
'''����content type Ϊ json'''
req.add_header('Content-Type', 'application/json')
try:
    response = urllib2.urlopen(req, request_json, 1)
    print response.read()
except urllib2.HTTPError as e:
    print e.exception.code