#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   identifer-text2bin.py
#        \author   chenghuige  
#          \date   2014-05-05 10:43:12.711473
#   \Description  
# ==============================================================================

import sys,os

from gezi import *

identifer = DoubleIdentifer()

print identifer.size()

identifer.load(sys.argv[1])

print identifer.size()

identifer.Save(sys.argv[2])
 
print 'finish!'

identifer2 = DoubleIdentifer()
identifer2.Load(sys.argv[2])

print identifer2.size()
