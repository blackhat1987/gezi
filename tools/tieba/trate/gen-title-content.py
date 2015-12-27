#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-title-content.py
#        \author   chenghuige  
#          \date   2015-12-25 10:04:45.929499
#   \Description  
# ==============================================================================

import sys,os
import nowarning
import libtieba

for line in open(sys.argv[1]):
	pid = line.rstrip().split()[0]
	pid = int(pid)
	info = libtieba.get_post_info(pid)
	print info.title,'\t',info.content.replace('\n', ' ')


 
