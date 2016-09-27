#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-reply-trate-label.py
#        \author   chenghuige  
#          \date   2014-12-11 21:16:17.906246
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
	l = line.split()
	print '%s\t%d'%(l[0], 1)

for line in open(sys.argv[2]):
	l = line.split()
	#if l[-2] == '热点吧' or l[-2] == '指定大型吧' or l[-2] == '全部':
	if l[-2] == '全部':
		print '%s\t%d'%(l[0], 0)
 
