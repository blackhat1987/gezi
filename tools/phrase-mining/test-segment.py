#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test-segment.py
#        \author   chenghuige  
#          \date   2015-08-18 10:51:11.003299
#   \Description  
# ==============================================================================

import sys,os
from libsegment import *

Segmentor.SetStrategy(SEG_USE_POSTAG)
Segmentor.Init()

handel = SegHandle()
handel.init()

for line in sys.stdin:
	print line
	#print Segmentor.Segment(line.strip(), '|')
	#print Segmentor.Segment(line.strip(), '|', SEG_BASIC)
	#print_seg_result()
	#print_seg_posttag_result()
	print Segmentor.Segment(line.strip(), '|', SEG_MERGE_NEWWORD)
	print_seg_result()
	#print_seg_posttag_result()
	#print line[:4]

	#Segmentor.segment(line.strip(), handel)
	#print_seg_result(handel)
	#print_seg_posttag_result(handel)

