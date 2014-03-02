#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-py.py
#        \author   chenghuige  
#          \date   2014-03-02 17:04:31.480595
#   \Description  
# ==============================================================================

import sys,os

print '''#inlcude "../include/python_util.h"'''
for line in open(sys.argv[1]):
	if(line.find('undefined call policies') < 0):
		print line,
	else:
		result = '            , bp::return_internal_reference<>())'
		if (line.find(';') >= 0):
			result += ';'
		print result

