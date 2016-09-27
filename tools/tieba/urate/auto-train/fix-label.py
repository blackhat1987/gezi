#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   fix-label.py
#        \author   chenghuige  
#          \date   2014-08-02 11:35:48.202381
#   \Description  
# ==============================================================================

import sys,os

lines = open(sys.argv[1]).readlines()
out = open(sys.argv[2], 'w')
out.write(lines[0])

l = lines[0].strip().split('\t')
m = {}

for i in range(len(l)):
	m[l[i]] = i

lines = lines[1:]

def need_label_spam(l):
	if int(l[m['label']]) == 0 and int(l[m['Sundry_HistorySize']]) == 10:
		if (float(l[m['Time_distinctDeltaRatio']]) <= 0.2 and float(l[m['Time_deltasMean']]) > 20):
			return True
		if int(l[m['Ip_numLocations']]) >= 9:
			return True 
	return False

label_changes = 0
for line in lines:
	l = line.strip().split()
	if need_label_spam(l):
		l[1] = '1'
		label_changes += 1
	out.write('\t'.join(l) + '\n')

print 'label_changes:',label_changes

