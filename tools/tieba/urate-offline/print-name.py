#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   print-name.py
#        \author   chenghuige  
#          \date   2015-03-02 18:56:23.883415
#   \Description  
# ==============================================================================

import sys,os
import gezi

l = gezi.uvec()
for line in open(sys.argv[1]):
	l.push_back(int(line.rstrip().split()[0]))
	if l.size() == 10000:
		break
print l.size()

l2 = gezi.get_users_info(l, False, False)
print l2.size()
for item in l2:
	print item.userName

 
