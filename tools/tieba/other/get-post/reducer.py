#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   reducer.py
#        \author   chenghuige  
#          \date   2015-02-09 19:15:32.001800
#   \Description  
# ==============================================================================

import sys,os

pre_word = None
total_count = 0

sep = '\t'
for line in sys.stdin:
	word, count = line.rstrip().split(sep, 1)
	try:
		count = int(count)
	except ValueError:
		continue
	total_count += count 
	if word != pre_word:
		if pre_word != None:
			print '%s\t%d'%(pre_word, total_count)
			total_count = 0
		pre_word = word 

if total_count > 0:
	print '%s\t%d'%(pre_word, total_count)
 
