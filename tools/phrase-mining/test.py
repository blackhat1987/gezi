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

librstree.setlocale_gbk()

tree = librstree.Rstree()
tree.set_max_substr_len(8)
tree.set_min_substr_len(2)
tree.set_min_frequency(1)

print '-----constructing suffix tree'

tree.add('exo')
tree.add('exom')
tree.add('exo')
tree.add('exod')
tree.add('exm')
print '-----finding phrases'

tree.write_result('t.txt')
l = tree.find_all_substrs()
#l = tree.find_all()
#l = sorted(l, cmp=lambda x,y : cmp(y.freq, x.freq))
print '-----sorting'
l = sorted(l, cmp=lambda x,y : cmp(y.second, x.second))

print '------top result'
for item in l:
	print item.first.encode('gbk'), item.second

print len(l)
#id = 0
#for item in l:
#	print '-----------------', id, (item.substr).encode('gbk'), item.freq 
#	for tid in item.tids:
#		print 'tid:',tid,'totalId:',tree.text_id(tid)
#		print tree.text(tid).encode('gbk')
#	id += 1 

print tree.find_freq('exo')
