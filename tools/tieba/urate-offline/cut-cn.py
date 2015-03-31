#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   cut-cn.py
#        \author   chenghuige  
#          \date   2015-03-06 14:40:14.908346
#   \Description  
# ==============================================================================

import sys,os
sys.path.append('./')
import gezi

sep = '\t'
for line in sys.stdin:
	l = line.rstrip('\n').split(sep)
	word = gezi.to_gbk(l[0])
	words = gezi.to_cnvec(gezi.extract_chinese(word))
	for word in words:
		print word
 
