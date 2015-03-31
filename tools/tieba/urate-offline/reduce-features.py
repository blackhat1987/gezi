#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   reduce-features.py
#        \author   chenghuige  
#          \date   2015-03-10 19:59:07.453448
#   \Description  
# ==============================================================================

import sys,os
sys.path.append('./')

import gezi 

def deal(li):
	if len(li) == 0:
		return
	feature_names = li[0][2].split(',')
	flen_ = len(feature_names)
	values = [0.0] * flen_
	values_min = [sys.float_info.max] * flen_
	values_max = [-sys.float_info.max] * flen_ 
	none_zeros = [0] * flen_
	len_ = float(len(li))
	id = li[0][0]
	for l in li:
		feature = l[1]
		fe = [] 
		if feature.find(',') >= 0:
			fe = feature.split(',')
		for item in fe:
			index, val = item.split(':')
			index = int(index)
			val = float(val)
			none_zeros[index] += 1
			values[index] += val 
			if val < values_min[index]:
				values_min[index] = val 
			if val > values_max[index]:
				values_max[index] = val 

	for index in range(flen_):
		if none_zeros[index] < len(li):
			if 0 < values_min[index]:
				values_min[index] = 0
			if 0 > values_max[index]:
				values_max[index] = 0

	fe = gezi.FeatureVector()	
	for i in range(flen_):
		name = feature_names[i]
		fe.add(values[i]/len_, name + '_avg')
		fe.add(values_min[i], name + '_min')
		fe.add(values_max[i], name + '_max')
	
	print '\t'.join([id, str(fe.Length()), fe.str(), fe.Str(), ','.join(fe.names())])


li = []
sep = '\t'
pre_key = None
for line in sys.stdin:
	l = line.rstrip('\n').split(sep)
	key = l[0]
	if key != pre_key:
		if pre_key != None:
			deal(li)
			li = []
		pre_key = key 
	li.append(l)

deal(li)

 
