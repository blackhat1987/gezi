#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   filter-pv.py
#        \author   chenghuige  
#          \date   2015-01-30 15:15:59.053253
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
	if line.find('指定大型吧') >= 0 or line.find('热点吧') >= 0:
		print line,

 
