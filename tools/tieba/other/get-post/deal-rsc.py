#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   deal-rsc.py
#        \author   chenghuige  
#          \date   2015-02-11 11:36:43.135205
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
	l = line.split('\x01')
	l[1] = '1'
	print '#'.join(l)

 
