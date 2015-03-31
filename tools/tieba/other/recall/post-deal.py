#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   post-deal.py
#        \author   chenghuige  
#          \date   2015-02-26 00:11:34.641148
#   \Description  
# ==============================================================================

import sys,os


count = int(open(sys.argv[2]).readline())

header = ['monitor_type', 'op_username', 'recall', 'total_count', 'self_recall', 'real_recall', 'recall_ratio', 'self_recall_ratio', 'real_recall_ratio']
print '\t'.join(header)

for line in open(sys.argv[1]):
	l = line.rstrip().split()
	l2 = []
	l2.append(l[0])
	l2.append(l[1])
	l2.append(l[2])
	l2.append(str(count))
	l2.append(str(int(float(l[3]))))
	l2.append(str(int(float(l[4]))))
	
	recall = int(l[2])
	self_recall =float(l[3])
	real_recall = float(l[4])

	recall_ratio = 1.0 * recall / count
	self_recall_ratio = 1.0 * self_recall / count
	real_recall_ratio = 1.0 * real_recall / count 
	l2.append(str(recall_ratio))
	l2.append(str(self_recall_ratio))
	l2.append(str(real_recall_ratio))

	print '\t'.join(l2)
	
