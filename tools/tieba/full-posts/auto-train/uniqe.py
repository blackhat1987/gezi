#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   uniqe.py
#        \author   chenghuige  
#          \date   2014-06-11 17:06:29.636145
#   \Description  
# ==============================================================================

import sys,os

s = {}
for line in open(sys.argv[1]):
	l = line.split('\t')
	if not l[0] in s:
		s[l[0]] = 1
		print line,

 
