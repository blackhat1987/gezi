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
seg = Segmentor()
seg.init()
s = 'a我爱你中华中华人民共和国第一检察院院长长春市长春药店读美文学作文'
print s
print seg.segment(s, '|')
s = '速去欧阳丹丹吧拿吧'
print seg.segment(s,'|')
print seg.segment('速去郭美美吧拿','|')
l = seg.segment('速去郭美美吧拿')
print l[0]
print seg.segment('马布里的扣扣是3212','|')

print seg.segment('马布里的扣扣是3212','|',SEG_MERGE_NEWWORD)

print seg.segment('abc def', '|')

