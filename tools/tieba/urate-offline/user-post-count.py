#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-edge.py
#        \author   chenghuige  
#          \date   2015-03-02 11:59:36.081399
#   \Description  
# ==============================================================================

import sys,os

sys.path.append('./')
import gezi

sep = '\t'
pre_key = None
li = []

def deal(li):
	count_set = set()
	thread_count_set = set()
	pic_count_set = set()
	for l in li:
		pid = l[1]
		title = gezi.to_gbk(l[-2])
		content = gezi.to_gbk(l[-1])
		
		count_set.add(pid)

		is_thread = False
		if gezi.is_thread(title):
			thread_count_set.add(pid)
			is_thread = True

		
		if is_thread and gezi.contains_pic(content):
			pic_count_set.add(pid)

	print l[0] + '\t' + str(len(count_set)) + '\t' + str(len(thread_count_set)) + '\t' + str(len(pic_count_set))

for line in sys.stdin:
	l = line.rstrip('\n').split(sep)
	if len(l) != 4:
		continue
	key = l[0]
	if key != pre_key:
		if pre_key != None:
			deal(li)
			li = []
	pre_key = key
	li.append(l)

deal(li)
 
