#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-evaluate-label.py
#        \author   chenghuige  
#          \date   2014-12-01 11:15:06.658024
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
	print line.split()[0] + '\t0'

 
