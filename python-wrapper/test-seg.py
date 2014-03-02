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

s = 'a�Ұ����л��л����񹲺͹���һ���ԺԺ�������г���ҩ�������ѧ����'
print s

s2 = segment(s)

print s2

s = '��ȥŷ���������ð�'
print segment(s)

print segment('��ȥ����������')

l = []
segment('��ȥ����������',l)
print l[0]
