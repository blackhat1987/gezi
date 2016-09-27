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
seg.segment_ts('abc def')
seg.GetSegHandle()
#h = SegHandle()
#print(seg.segment('abc def', h, '|'))
