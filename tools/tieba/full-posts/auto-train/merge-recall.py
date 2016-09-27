#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   merge-recall.py
#        \author   chenghuige  
#          \date   2014-12-02 17:02:46.009557
#   \Description  
# ==============================================================================

import sys,os

s = set()
for line in open(sys.argv[1]):
	s.add(line.strip().split()[0])
	print line,

s2 = set()
for line in open(sys.argv[2]):
	pid = line.strip().split()[0]
	s2.add(pid)
	if pid not in s:
		print line,

#print 's2 difference s:%d'%len(s2.difference(s))
#print 's difference s2:%d'%len(s.difference(s2))

