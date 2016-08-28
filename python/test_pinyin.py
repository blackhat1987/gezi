#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test_pinyin.py
#        \author   chenghuige  
#          \date   2016-03-24 16:22:40.121376
#   \Description  
# ==============================================================================

  
from __future__ import absolute_import
from __future__ import division
#from __future__ import print_function

import sys,os
import libpinyin 
import libstringutil

conv = libpinyin.Pinyin()

ret = conv.Load('./data/pinyin/')

print ret 

print conv.Convert('���')
print conv.Convert('��úŵļǺŵĹ���')

s = '���123 abc��'
print s
print conv.Convert(s)

s = libstringutil.extract_chinese(s)
print s
print conv.Convert(s)

  
