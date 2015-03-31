#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   get-hive-table-header.py
#        \author   chenghuige  
#          \date   2015-03-07 21:34:31.681047
#   \Description  
# ==============================================================================

import sys,os

l = []
for line in open(sys.argv[1]):
	a,b = line.rstrip().split('\t', 1)
	l.append(a)

print ','.join(l)

 
