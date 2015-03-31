#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test.py
#        \author   chenghuige  
#          \date   2015-03-06 14:37:25.012375
#   \Description  
# ==============================================================================

import sys,os

s = set()
for line in open(sys.argv[1]):
	uid = line.split()[0]
	if uid in s:
		print uid 
	s.add(uid)

print len(s)
 
