#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-py.py
#        \author   chenghuige  
#          \date   2014-03-02 17:04:31.480595
#   \Description  
# ==============================================================================

import sys,os

find = False
find_warning = False
print '''#include "../include/python_util.h"'''
for line in open(sys.argv[1]):
	if(line.find('undefined call policies') < 0):
		if (find_warning):
			print '//',
			find_warning = False
		line = line.replace('.h.python', '.h').replace('include.python','include')
		line = line.replace('boost::unordered','std')
		print line,
		if (line.find('WARNING:') >= 0):
			find_warning = True 
		if (find == False and line.find('BOOST_PYTHON_MODULE') >= 0):
			find = True
			print '''DEF_VEC(ivec);
			DEF_VEC(dvec);
			DEF_VEC(uvec);
			DEF_VEC(svec);
			DEF_VEC(ulvec);
			DEF_MAP(id_map);
			DEF_MAP(sd_map);
			DEF_MAP(si_map);
			'''
	else:
		result = '            , bp::return_internal_reference<>())'
		if (line.find(';') >= 0):
			result += ';'
		print result

