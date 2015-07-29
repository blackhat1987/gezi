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
tree.set_min_substr_len(2)
tree.set_min_frequency(3)

tree.add(('����˭').decode('gbk'))
tree.add(('����˭').decode('gbk'))
tree.add(('����˭').decode('gbk'))
tree.add(('abc').decode('gbk'))
tree.add(('abc').decode('gbk'))
tree.add(('abc').decode('gbk'))


tree.add('����˭'.decode('gbk'))
tree.add('����˭'.decode('gbk'))
tree.add('����˭'.decode('gbk'))
tree.add('÷����һ����Ա'.decode('gbk'))
tree.add('c����һ����Ա'.decode('gbk'))
tree.add('����˭��÷��'.decode('gbk'))
tree.add('������Ա÷�������ʤ��'.decode('gbk'))

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

print tree.text(0).encode('gbk')

l = tree.find_all()
id = 0
for item in l:
	print '-----------------', id, (item.substr).encode('gbk'), item.freq 
	for tid in item.tids:
		print 'tid',tid
		#print tree.text(tid).encode('gbk')
	id += 1
