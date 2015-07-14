#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   frspids2uids.py
#        \author   chenghuige  
#          \date   2015-03-23 17:25:35.607004
#   \Description  
# ==============================================================================

import sys,os
import gezi 

pids = gezi.ulvec()
for line in open(sys.argv[1]):
	l = line.rstrip('\n').split('\t')
	if l[-2].startswith('指定') or l[-2].startswith('热点'):
		pids.append(int(l[0]))

results = gezi.get_posts_info_map(pids)

s = set()
for item in results:
	s.add(item.data().forumId)

for fid in s:
	print fid
	

 
