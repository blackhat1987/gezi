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

max_len = 8
min_len = 2
min_freq = 5

librstree.setlocale_gbk()

tree = librstree.Rstree()
tree.set_max_substr_len(max_len)
tree.set_min_substr_len(min_len)
tree.set_min_frequency(min_freq)

normalizer = libchnormalizer.ChNormalizer()
normalizer.Init()
print '-----constructing reverse suffix tree'
nword = 0

phrases_info = {}

texts = []
for line in open(sys.argv[1]):
	line = line.strip()
	line = libstringutil.filter_str(normalizer.Normalize(line))
	texts.append(line)
	tree.add(line.decode('gbk', 'ignore')[::-1])
	nword += len(line)
	if tree.size() % 1000 == 0:
		print tree.size()

print '-----finding phrases'
l = tree.find_all_substrs()

print '-----calc left information'
for item in l:
	rinfo = tree.right_information(item.first)
	phrases_info[item.first[::-1]] = {'linfo' : rinfo}

#tree.reset()  #@FIXME reset not work... will core later

tree = librstree.Rstree()
tree.set_max_substr_len(max_len)
tree.set_min_substr_len(min_len)
tree.set_min_frequency(min_freq)

print '-----constructing suffix tree'
for line in texts:
	tree.add(line.decode('gbk', 'ignore'))
	if tree.size() % 1000 == 0:
		print tree.size()
	
print '-----finding phrases'
l = tree.find_all_substrs()

print '-------calc pmi and right information'
for item in l:
	if item.first not in phrases_info:
		continue
	prefix_vec = librstree.ivec()
	suffix_vec = librstree.ivec()
	tree.find_prefix_suffix_freqs(item.first, prefix_vec, suffix_vec)
	min_pmi = 10000000000000000.0 
	min_pkl = min_pmi
	for i in range(len(prefix_vec)):
		pmi = libnumeric.point_mutual_info(item.second, prefix_vec[i], suffix_vec[i], nword)
		pkl = item.second / float(nword) * pmi 
		if pmi < min_pmi:
			min_pmi = pmi
		if pkl < min_pkl:
			min_pkl = pkl
	pinfo = phrases_info[item.first]
	pinfo['pmi'] = min_pmi
	pinfo['pkl'] = min_pkl
	rinfo = tree.right_information(item.first)
	pinfo['rinfo'] = rinfo
	pinfo['freq'] = item.second


print '--------get seg info'
seg_results = [[]] * len(texts)
from libsegment import * 
Segmentor.Init()

num = 0
for item in l:
	num += 1
	if num % 1000 == 0:
		print num, float(num) / len(l)
	if item.first not in phrases_info:
		continue

	#if item.first.encode('gbk', 'ignore') != '警察':
	#	continue

	pinfo = phrases_info[item.first]
	vec = tree.get_texts_id_pos(item.first)
	unmatch = 0
	fullmatch = 0
	for pair in vec:
		text = texts[pair.first]
		#start = pair.second 
		len_ = len(item.first)
		#start = start - len_
		start = text.decode('gbk', 'ignore').find(item.first)
		end = start + len_
		if len(seg_results[pair.first]) == 0:
			svec_ = Segmentor.Segment(text, SEG_MERGE_NEWWORD)
			#print Segmentor.Segment(text, '|', SEG_MERGE_NEWWORD)
			lvec_ = [0] * (len(svec_) + 1)
			for i in range(len(svec_)):
				lvec_[i + 1] = len(svec_[i].decode('gbk', 'ignore'))
			for i in range(1, len(svec_) + 1):
				lvec_[i] = lvec_[i - 1] + lvec_[i]
			seg_results[pair.first] = lvec_

		lvec_ = seg_results[pair.first]
		#print lvec_
		match_start = False
		match_end = False 
		match_phrase = False
		pre_pos = 0
		for pos in lvec_:
			if pos == start:
				#print '==start:', pos
				match_start = True 
			if pos == end:
				#print '==end:', pos
				match_end = True
				if match_start and pre_pos == start:
					match_phrase = True 
			pre_pos = pos
	
		#print item.first.encode('gbk'), start, end
		#print 'match_phrase:', match_phrase
		#print 'match_start:', match_start
		#print 'match_end:', match_end
		if match_phrase:
			fullmatch += 1
		elif not match_start or not match_end:
			unmatch += 1
	
	#print item.first.encode('gbk'), unmatch, item.second
	if unmatch / float(item.second) > 0.5:
		pinfo['label'] = 0

	if fullmatch / float(item.second) > 0.1:
		pinfo['label'] = 1

out_train = open('phrase.train.txt', 'w')
out_train.write('#phrase\tlabel\tfreq\tprob\tlength\tpmi\tpkl\trinfo\tlinfo\n')
for (phrase, pinfo) in phrases_info.items():
	if 'freq' in pinfo and 'label' in pinfo:
		label = pinfo['label']
		out_train.write('_%s\t%d\t%d\t%f\t%d\t%f\t%f\t%f\t%f\n'%(phrase.encode('gbk', 'ignore'), label, pinfo['freq'], pinfo['freq'] / float(nword), len(phrase), pinfo['pmi'], pinfo['pkl'], pinfo['rinfo'], pinfo['linfo']))

out = open('phrase.feature.txt', 'w')
out.write('#phrase\tlabel\tfreq\tprob\tlength\tpmi\tpkl\trinfo\tlinfo\n')
label = 0
for (phrase, pinfo) in phrases_info.items():
	if 'freq' in pinfo and 'label' not in pinfo:
		out.write('_%s\t%d\t%d\t%f\t%d\t%f\t%f\t%f\t%f\n'%(phrase.encode('gbk', 'ignore'), label, pinfo['freq'], pinfo['freq'] / float(nword), len(phrase), pinfo['pmi'], pinfo['pkl'], pinfo['rinfo'], pinfo['linfo']))

