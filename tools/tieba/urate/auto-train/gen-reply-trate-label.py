#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-reply-trate-label.py
#        \author   chenghuige  
#          \date   2014-12-11 21:16:17.906246
#   \Description  
# ==============================================================================

import sys,os

count1 = 0
for line in open(sys.argv[1]):
	l = line.split()
	count1 += 1
	print '%s\t%d'%(l[0], 1)

count2 = 0
for line in open(sys.argv[2]):
	l = line.split()
	if l[2] == '热点吧' or l[2] == '指定大型吧':
		count2 += 1
		if count2 > count1 * 10:
			break
		print '%s\t%d'%(l[0], 0)
 
