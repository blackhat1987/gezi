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
s = 'a�Ұ����л��л����񹲺͹���һ���ԺԺ�������г���ҩ�������ѧ����'
print s
print seg.segment(s, '|')
s = '��ȥŷ���������ð�'
print seg.segment(s,'|')
print seg.segment('��ȥ����������','|')
l = seg.segment('��ȥ����������')
print l[0]
print seg.segment('����Ŀۿ���3212','|')

print seg.segment('����Ŀۿ���3212','|',SEG_MERGE_NEWWORD)

print seg.segment('abc def', '|')

