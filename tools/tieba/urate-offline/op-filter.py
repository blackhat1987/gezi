#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   op-filter.py
#        \author   chenghuige  
#          \date   2015-03-02 17:15:06.828377
#   \Description  
# ==============================================================================

import sys,os
sys.path.append('./')
import gezi 

for line in sys.stdin:
	l = line.rstrip().split('\t')
	opname = gezi.to_gbk(l[-1])
	if opname.startswith('贴吧'):
		print line,
 
