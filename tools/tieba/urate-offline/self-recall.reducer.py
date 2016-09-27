#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   self-recall.reducer.py
#        \author   chenghuige  
#          \date   2015-02-25 16:46:34.816350
#   \Description  
# ==============================================================================

import sys,os

pre_word = None

li = []
sep = '\t'

def deal(li):
	if len(li) == 0:
		return
	elif len(li) == 1:
		li[0].append('1')
		li[0].append('1')
		print sep.join(li[0])
	else:
		best_priority = int(li[0][-1])
		if int(li[1][-1]) != best_priority:
			li[0].append('1')
			li[0].append('1')
			print sep.join(li[0])
			li = li[1:]
			for l in li:
				l.append('0')
				l.append('0')
				print sep.join(l)
		else:
			for l in li:
				l.append('0')
				if int(l[-1]) == best_priority:
					l.append('1')
				else:
					l.append('0')
				print sep.join(l)

for line in sys.stdin:
	l = line.rstrip().split(sep)
	word = l[0]
	if word != pre_word:
		if pre_word != None:
			deal(li)
			li = []
		pre_word = word 
	li.append(l)

deal(li)

