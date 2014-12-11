#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   split-thread-reply.py
#        \author   chenghuige  
#          \date   2014-11-28 17:18:24.876710
#   \Description  
# ==============================================================================

import sys,os

out_threads = open('for_evaluate.thread.txt', 'w')
out_replys = open('for_evaluate.reply.txt', 'w')
for line in open(sys.argv[1]):
	l = line.strip().split('\t')
	title = l[-3]
	content = l[-2]
	if not title.startswith('回复：'):
		out_threads.write(line)
	else:
		out_replys.write(line)
 
