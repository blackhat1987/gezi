#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   add-header.py
#        \author   chenghuige  
#          \date   2015-03-05 13:55:38.184559
#   \Description  
# ==============================================================================

import sys,os

for line in sys.stdin:
	uid, label, feature_len, feature = line.rstrip().split('\t')
	values = ['0'] * int(feature_len)
	features = feature.split(',')
	for item in features:
		l = item.split(':')
		index = int(l[0])
		value = l[1]
		values[index] = value
	values = ['_' + uid, label] + values
	print ','.join(values)
 
