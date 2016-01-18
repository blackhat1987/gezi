#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   to-lego.py
#        \author   chenghuige  
#          \date   2016-01-05 20:31:14.199332
#   \Description  
# ==============================================================================

import sys,os


num = 1
for line in open(sys.argv[1]):
	l = line.strip().split('\t')
	id = l[0][1:]
	label = l[1]
	start = 3
	fe = []
	for i in xrange(start, len(l)):
		index = l[i].split(':')[0]
		fe.append(index)
	#print '{};{};{}'.format(num,' '.join(fe),label)
	print '{};{};{}'.format(id,' '.join(fe),label)
	num += 1

 
