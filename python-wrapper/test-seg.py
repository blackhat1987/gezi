#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test-seg.py
#        \author   chenghuige  
#          \date   2014-03-01 13:32:30.259515
#   \Description  
# ==============================================================================

import sys,os
from libgezi import *

LogHelper.set_level(4)

seg_init('./data/wordseg/', 0, './conf/scw.conf')

s = 'a我爱你中华中华人民共和国第一检察院院长长春市长春药店读美文学作文'
print s

s2 = segment(s)

print s2

s = '速去欧阳丹丹吧拿吧'
print segment(s)

print segment('速去郭美美吧拿')

l = []
segment('速去郭美美吧拿',l)
print l[0]
