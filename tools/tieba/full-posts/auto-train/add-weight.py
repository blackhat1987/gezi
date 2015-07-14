#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   add-weight.py
#        \author   chenghuige  
#          \date   2015-01-30 10:55:45.399819
#   \Description  
# ==============================================================================

import sys,os

is_first = True
for line in open(sys.argv[1]):
	l = line.strip().split()
	if is_first:
		l.insert(2, 'weight')
		print '\t'.join(l)
		is_first = False
	else:
		weight = 1.0
		if l[1] == '1':
			weight = weight * int(sys.argv[2])
		l.insert(2, str(weight))
		print '\t'.join(l)


 
