#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   add-baduids.py
#        \author   chenghuige  
#          \date   2015-03-13 14:29:19.317785
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
	print line,
for line in open(sys.argv[2]):
	print line.replace(',', '\t'),

 
