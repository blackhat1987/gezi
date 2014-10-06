#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   fix-add-more-vector.py
#        \author   chenghuige  
#          \date   2014-10-06 17:59:31.486882
#   \Description  
# ==============================================================================

import sys,os

s = set()
def add_vector(line, name):
	if line.strip().startswith('%s_exposer.def'%name):
		item = 'VEC_METHOD2({0}_exposer, gezi::{0});'.format(name)
		if not item in s:
			s.add(item)
			print item

for line in open(sys.argv[1]):
	add_vector(line, 'Vector')
	add_vector(line, 'FeatureVector')
	print line,

 
