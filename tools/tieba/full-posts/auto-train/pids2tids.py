#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   pids2tids.py
#        \author   chenghuige  
#          \date   2014-09-19 19:34:39.385042
#   \Description  
# ==============================================================================

import sys,os
import warnings
warnings.simplefilter("ignore", RuntimeWarning) 
import libtieba

out = open(sys.argv[2], 'w')
lines = open(sys.argv[1]).readlines()
linelist = [line.strip().split() for line in lines]
pids = [l[0] for l in linelist]

m = {}
for l in linelist:
	m[long(l[0])] = l[1]

pidvec = libtieba.vector_less__long_long_unsigned_int__greater_()
for pid in pids:
	pidvec.append(long(pid))

print len(pidvec)
results = libtieba.get_posts_info(pidvec)

for item in results:
	if (item.postId == 0):
		continue
	item.title = item.title.replace('\n', ' ')
	item.content = item.content.replace('\n', ' ')
	out.write("%s\n"%("\t".join([str(item.threadId), m[item.postId], str(item.postId), item.title, item.content])))

print len(results)


 
