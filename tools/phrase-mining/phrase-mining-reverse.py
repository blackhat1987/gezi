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
import libnumeric
import libstringutil
import libchnormalizer

librstree.setlocale_gbk()

tree = librstree.Rstree()
tree.set_max_substr_len(8)
tree.set_min_substr_len(2)
tree.set_min_frequency(5)

normalizer = libchnormalizer.ChNormalizer()
normalizer.Init()
print '-----constructing reverse suffix tree'

nword = 0
for line in open(sys.argv[1])
	line = line.strip()
	line = libstringutil.filter_str(normalizer.Normalize(line))
	tree.add(line.decode('gbk', 'ignore')[::-1])
	nword += len(line)
	if tree.size() % 1000 == 0:
		print tree.size()
	#if tree.size() > 10000000:
	#	break

#tree.write_result('t.txt')

print '-----finding phrases'
l = tree.find_all_substrs()
#l = tree.find_all()
#l = sorted(l, cmp=lambda x,y : cmp(y.freq, x.freq))
print '-----sorting'
l = sorted(l, cmp=lambda x,y : cmp(y.second, x.second))

print '------top result'

#out = open('pmi.result.txt', 'w')
#for item in l:
#	#print item.first.encode('gbk'), item.second
#	prefix_vec = librstree.ivec()
#	suffix_vec = librstree.ivec()
#	tree.find_prefix_suffix_freqs(item.first, prefix_vec, suffix_vec)
#	min_pmi = 10000000000000000.0
#	for i in range(len(prefix_vec)):
#		pmi = libnumeric.point_mutual_info(item.second, prefix_vec[i], suffix_vec[i], nword)
#		if pmi < min_pmi:
#			min_pmi = pmi 
#	out.write('%s\t%f\n'%(item.first.encode('gbk'), min_pmi))


out2 = open('linfo.result.txt', 'w')
for item in l:
	rinfo = tree.right_information(item.first)
	out2.write('%s\t%f\n'%(item.first[::-1].encode('gbk'), rinfo))

print len(l)
#id = 0
#for item in l:
#	print '-----------------', id, (item.substr).encode('gbk'), item.freq 
#	for tid in item.tids:
#		print 'tid:',tid,'totalId:',tree.text_id(tid)
#		print tree.text(tid).encode('gbk')
#	id += 1 

