#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-label.py
#        \author   chenghuige  
#          \date   2014-11-27 09:26:50.208926
#   \Description  
# ==============================================================================

import sys,os

count1 = 0
for line in open(sys.argv[1]):
	l = line.split()
	print '%s\t%d'%(l[0], 1)
	count1 += 1

count1 *= 10
count2 = 0
for line in open(sys.argv[2]):
	l = line.split()
	print '%s\t%d'%(l[0], 0)
	count2 += 1
	if count2 > count1:
		break

 
