#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   filter-pv.py
#        \author   chenghuige  
#          \date   2015-01-30 15:15:59.053253
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
	if line.find('ָ�����Ͱ�') >= 0 or line.find('�ȵ��') >= 0:
		print line,

 
