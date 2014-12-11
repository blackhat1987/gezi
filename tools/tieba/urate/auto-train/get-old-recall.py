#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   get-old-recall.py
#        \author   chenghuige  
#          \date   2014-12-02 16:34:11.469937
#   \Description  
# ==============================================================================

import sys,os

thre = float(sys.argv[2])
for line in open(sys.argv[1]):
	l = line.strip().split()
	pid = l[0]
	score = float(l[-1])
	if score < thre:
		break
	print pid,'\t',score

 
