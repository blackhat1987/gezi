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
	louzhu_uid = None
	m = {}
	for l in li:
		uid = l[1]
		title = gezi.to_gbk(l[2])
		if gezi.is_thread(title):
			louzhu_uid = uid
		else:
			if not uid in m:
				m[uid] = 1
			else:
				m[uid] += 1
	if louzhu_uid != None:
		for (uid, count) in m.items():
			if uid != louzhu_uid:
				print louzhu_uid + '\t' + uid + '\t' + str(count)

for line in sys.stdin:
	l = line.rstrip().split(sep)
	if len(l) != 3:
		continue
	key = l[0]
	if key != pre_key:
		if pre_key != None:
			deal(li)
			li = []
	pre_key = key
	li.append(l)

deal(li)
 
