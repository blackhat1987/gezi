#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   convertCnCount2Ratio.py
#        \author   chenghuige  
#          \date   2015-03-06 17:28:20.236489
#   \Description  
# ==============================================================================

import sys,os
import math

total_count = 0
cns = []
counts = []
for line in open(sys.argv[1]):
	cn, count = line.strip().split()
	count = int(count)
	total_count += count 
	cns.append(cn)
	counts.append(count)

for i in range(len(counts)):
	counts[i] = (counts[i] * 1.0) /total_count
	print '%s\t%f'%(cns[i], -math.log(counts[i]))
 
