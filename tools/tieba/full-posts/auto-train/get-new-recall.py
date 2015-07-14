#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   get-new-recall.py
#        \author   chenghuige  
#          \date   2014-12-02 16:44:18.550398
#   \Description  
# ==============================================================================

import sys,os

max_num = int(os.popen('wc -l %s'%sys.argv[1]).read().split()[0])
max_num = int(max_num * 1.2)
num = 0
for line in open(sys.argv[2]):
	if num == 0:
		num += 1
		continue
	if num == max_num:
		break
	l = line.strip().split()
	pid = l[0]
	score = l[-1]
	num += 1
	print pid,'\t',score
	


 
