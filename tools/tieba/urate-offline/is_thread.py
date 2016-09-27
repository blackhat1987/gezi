#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   is_thread.py
#        \author   chenghuige  
#          \date   2015-02-15 21:34:05.604659
#   \Description  
# ==============================================================================

import sys,os

sys.path.append('./')
from gezi import *
LogHelper.set_level(4)

for line in sys.stdin:
	l = line.rstrip().split('\t')
	title = l[-1]
	title = to_gbk(title)
	if is_thread(title):
		print '\t'.join(l)
 
