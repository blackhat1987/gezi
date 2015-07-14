#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   add-header.py
#        \author   chenghuige  
#          \date   2015-03-05 13:55:38.184559
#   \Description  
# ==============================================================================

import sys,os

l = ['#id', 'label']
l += open(sys.argv[1]).readline().rstrip().split(',')
print '\t'.join(l)

for line in open(sys.argv[2]):
	print '_' + line.rstrip().replace(',','\t')
 
