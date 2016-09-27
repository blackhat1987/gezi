#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   diff.py
#        \author   chenghuige  
#          \date   2014-12-09 15:49:52.198262
#   \Description  
# ==============================================================================

import sys,os


out_left = open('out_left.txt', 'w')
out_right = open('out_right.txt', 'w')

max_num = int(sys.argv[3])
lefts = [line.strip().split()[0] for line in open(sys.argv[1])][1:max_num]
rights = [line.strip().split()[0] for line in open(sys.argv[2])][1:max_num]

print len(lefts)
print len(rights)

lefts_set = set()
for item in lefts:
	lefts_set.add(item)

rights_set = set()
for item in rights:
	rights_set.add(item)

l = lefts_set.difference(rights_set)
print len(l)
for item in l:
	out_left.write('%s\n'%item)

r = rights_set.difference(lefts_set)
print len(r)
for item in r:
	out_right.write('%s\n'%item)
