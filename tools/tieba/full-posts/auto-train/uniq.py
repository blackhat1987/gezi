#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   uniq.py
#        \author   chenghuige  
#          \date   2014-12-09 17:20:14.428674
#   \Description  
# ==============================================================================

import sys,os

s = set()

for line in open(sys.argv[1]):
	pid = line.strip().split()[0]
	if pid not in s:
		s.add(pid)

print len(s)

 
