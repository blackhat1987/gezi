#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   add-header.py
#        \author   chenghuige  
#          \date   2015-03-05 13:55:38.184559
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
	print line,

for line in open(sys.argv[2]):
	print line.replace(',','\t'),
 
