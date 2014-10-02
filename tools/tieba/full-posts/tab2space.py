#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   tab2space.py
#        \author   chenghuige  
#          \date   2014-10-02 12:26:19.444438
#   \Description  
# ==============================================================================

import sys,os

input = object
if len(sys.argv) > 1:
	input = open(sys.argv[1])
else:
	input = sys.stdin

for line in input:
	print line.replace('\t', ' '),
 
