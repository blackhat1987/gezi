#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-py.py
#        \author   chenghuige  
#          \date   2014-03-02 17:04:31.480595
#   \Description  
# ==============================================================================

import sys,os

print '''#include "../include/python_util.h"'''
for line in open(sys.argv[1]):
	if(line.find('undefined call policies') < 0):
		print line,
		if (line.find('BOOST_PYTHON_MODULE') >= 0):
			print '''UseStrVec;
			UseIntVec;
			UseFloatVec;
			UseDoubleVec;
			UseStrStrMap;
			UseStrIntMap;
			UseStrFloatMap;
			UseStrDoubleMap;
			'''
	else:
		result = '            , bp::return_internal_reference<>())'
		if (line.find(';') >= 0):
			result += ';'
		print result

