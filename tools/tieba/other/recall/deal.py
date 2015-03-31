#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   deal.py
#        \author   chenghuige  
#          \date   2015-02-25 14:51:33.326227
#   \Description  
# ==============================================================================

import sys,os

print sys.argv[1]
for line in open(sys.argv[1]):
	print line.replace('#', '\x01'),

 
