#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   word-count.py
#        \author   chenghuige  
#          \date   2015-10-30 10:51:19.133589
#   \Description  
# ==============================================================================

import sys,os
from collections import defaultdict
import operator

word_count_map = {}
word_count_map = defaultdict(lambda:0, word_count_map)

eos_tag = '</s>'

count = 0

input = sys.stdin 
if len(sys.argv) > 1:
	input = open(sys.argv[1])

for line in input:
	if count % 100000 == 0:
		print >> sys.stderr, count 
	count += 1

	l = line.strip().split()
	l.append(eos_tag)

	for item in l:
		word_count_map[item] += 1

print >> sys.stderr, 'Process totoal ', count 
print >> sys.stderr, 'Begin sort'

word_count_map = sorted(word_count_map.items(), key=operator.itemgetter(1), reverse=True)

for key,val in word_count_map:
	print key,'\t',val
