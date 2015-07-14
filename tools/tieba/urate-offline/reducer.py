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
	pass

for line in sys.stdin:
	l = line.rstrip().split(sep)
	key = l[0]
	if key != pre_key:
		if pre_key != None:
			deal(li)
			li = []
	pre_key = key
	li.append(l)

deal(li)
 
