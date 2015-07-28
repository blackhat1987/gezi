#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test-rstree.py
#        \author   chenghuige  
#          \date   2015-07-25 10:11:46.995736
#   \Description  
# ==============================================================================

import sys,os

import nowarning 
import librstree 

from librstree import wstr 
from librstree import wstr2str

librstree.setlocale_gbk()

tree = librstree.Rstree()
tree.set_max_substr_len(5)
tree.set_min_substr_len(3)
tree.set_min_frequency(3)

tree.add(wstr('你是谁'))
tree.add(wstr('你是谁'))
tree.add(wstr('你是谁'))
tree.add('abc')
tree.add('abc')
tree.add('abc')

tree.add('我是谁'.decode('gbk'))
tree.add('我是谁'.decode('gbk'))
tree.add('我是谁'.decode('gbk'))

l = tree.find_all_substrs()

print len(l)

for item in l:
	#print wstr2str(item.first),item.second
	print (item.first).encode('gbk'),item.second

tree.remove()
tree.remove()
tree.remove()

l = tree.find_all_substrs()
print len(l)

for item in l:
	print (item.first).encode('gbk'), item.second
 
