#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   seg-new-word.py
#        \author   chenghuige  
#          \date   2015-02-08 18:35:48.068824
#   \Description  
# ==============================================================================

import sys,os
sys.path.append('./')
from gezi import *
LogHelper.set_level(4)
Segmentor.Init()
sep ='\x02'
#for line in open(sys.argv[1]):
for line in sys.stdin:
	l = Segmentor.Segment(line.rstrip(), SEG_NEWWORD)
	l = vec2list(l)
	if len(l) > 0:
		print sep.join(l)


 
