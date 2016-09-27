#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   filter-by-postnum.py
#        \author   chenghuige  
#          \date   2015-07-04 22:46:55.501296
#   \Description  
# ==============================================================================

import sys,os

is_first = True
for line in open(sys.argv[1]):
	if is_first:
		is_first = False
		print line,
		continue
	l = line.split()
	if int(l[3]) < 2:
		print line,



 
