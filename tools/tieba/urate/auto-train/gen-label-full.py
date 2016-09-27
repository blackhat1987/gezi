#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-label.py
#        \author   chenghuige  
#          \date   2014-11-27 09:26:50.208926
#   \Description  
# ==============================================================================

import sys,os

num_max_pos = 20000

count = 0
date = ''
for line in open(sys.argv[1]):
	l = line.split()
	print '%s\t%d'%(l[0], 1)
	count += 1
	if count > num_max_pos:
		date = l[3]
		break

for line in open(sys.argv[2]):
	l = line.split()
	if date != '' and date > l[3]:
		break 
	print '%s\t%d'%(l[0], 0)

 
