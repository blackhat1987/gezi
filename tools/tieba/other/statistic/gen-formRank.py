#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-formRank.py
#        \author   chenghuige  
#          \date   2015-02-16 18:38:23.135341
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
	line = line.rstrip().decode('utf8').encode('gbk')
	l = line.rstrip().split('\x01')
	print '%s\t%s'%(l[0], l[3])

 
