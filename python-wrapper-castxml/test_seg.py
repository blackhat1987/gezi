#!/usr/bin/env python
# -*- coding: gbk -*-
# ==============================================================================
#          \file   test_seg.py
#        \author   chenghuige  
#          \date   2016-11-04 15:49:31.564556
#   \Description  
# ==============================================================================

  
from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import libsegment 
from libsegment import Segmentor, SegHandle

text = '刘亦菲和朴姬兰在韩国举行演唱会' 

Segmentor.Init()
#print(Segmentor.Segment(text, '|', libsegment.SEG_MERGE_NEWWORD))

#Segmentor.init()
#Segmentor.SetStrategy(libsegment.SEG_USE_OFFSETS)
#seg = Segmentor()
#handle = SegHandle()
##handle.init()
#seg.segment(text, handle, libsegment.SEG_MERGE_NEWWORD)
##seg.segment(text, handle, libsegment.SEG_BASIC)
##libsegment.print_seg_result(Segmentor.get_handle())
##libsegment.print_seg_result(handle)
#
#for i in range(handle.nresult):
#  print(handle.word(i), handle.offset(i), handle.len(i))
#

vec = Segmentor.Cut(text)
for item in vec:
  print(item.word, item.offset, item.length, item.type, item.weight)
