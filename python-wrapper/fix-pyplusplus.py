#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-py.py
#        \author   chenghuige  
#          \date   2014-03-02 17:04:31.480595
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
	if(line.find('undefined call policies') < 0):
		print line
	else:
		print '            , bp::return_internal_reference<>())'
