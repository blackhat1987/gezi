#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   print-info.py
#        \author   chenghuige  
#          \date   2015-03-11 12:04:05.336734
#   \Description  
# ==============================================================================

import sys,os
sys.path.append('./')

sep = '\t'

def deal(li):
	if len(li) == 0:
		return
	uid = ''
	uname = ''
	score = ''
	feature_len = ''
	feature = ''
	fnames = []
	titles = []
	contents = []
	post_ids = []
	for l in li:
		[uid, uname, score, post_id, fname, title, content, feature_len, feature] = l
		fnames.append(fname)
		titles.append(title)
		contents.append(content)
		post_ids.append(post_id)

	print sep.join([uid, uname, score, post_ids[0], '$'.join(fnames[:5]), '#'.join(titles[:5]),'%'.join(contents[:3]), feature_len, feature])
		

li = []
pre_key = None
for line in sys.stdin:
	l = line.rstrip('\n').split(sep)
	try:
		[uid, uname, score, post_id, fname, title, content, feature_len, feature] = l
	except Exception:
		continue
	key = l[0]
	if key != pre_key:
		if pre_key != None:
			deal(li)
			li = []
		pre_key = key 
	li.append(l)

deal(li)
 
