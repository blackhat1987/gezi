#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   mapper.py
#        \author   chenghuige  
#          \date   2015-02-09 19:15:27.101902
#   \Description  
# ==============================================================================

import sys,os

sep = '\x02'
for line in sys.stdin:
	l = line.rstrip().split(sep)
	for word in l:
		print word
 
