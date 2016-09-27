#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-label.py
#        \author   chenghuige  
#          \date   2014-11-27 09:26:50.208926
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
	l = line.split()
	print '%s\t%d'%(l[0], 1)

for line in open(sys.argv[2]):
	l = line.split()
	print '%s\t%d'%(l[0], 0)

 
