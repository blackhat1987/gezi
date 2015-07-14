#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   seg-text.py
#        \author   chenghuige  
#          \date   2014-03-08 17:01:57.385278
#   \Description  input is like urate feature file, ouput (pid, label, seged title, seged content)
#                 get title, content from db
# ==============================================================================

import sys, os
from gezi import *

LogHelper.set_level(4)
Segmentor.Init()
print Segmentor.Segment('我的扣扣是', '|', SEG_BASIC)
total = len(open(sys.argv[1]).readlines())
print 'total: %d'%total 
_pb = ProgressBar(total)
_identifer = Idf()
out = open(sys.argv[2], 'w')
types = ["pic", "url", "num", "at"]
sep = '$#$'
num = 0
for line in open(sys.argv[1]):
	_pb.progress(num)
	try:
		l = line.strip().split('\t')
		pid = l[0]
		label = l[1]
		title = l[2]
		content = ''
		if (len(l) == 4):
			content = l[3]
		title = get_real_title(title)
		tvec = Segmentor.Segment(title, SEG_BASIC)
		_identifer.add(tvec)
		title = sep.join(tvec)
		src = title + " " + content 
		has_pic = int(contains_any(src, "pic"))
		has_url = int(contains_any(src, "url"))
		has_num = int(contains_any(src, "num"))
		has_at = int(contains_any(src, "at"))
		content = strip_html(content)
		if len(content) > 100:
			content = gbk_substr(content, 0, 100)
		#content = normalize_str(content)
		cvec = Segmentor.Segment(content, SEG_BASIC)
		_identifer.add(cvec)
		content = sep.join(cvec)
		out.write( '%s\n'%('\t'.join([pid, label, str(has_pic), str(has_url), str(has_num), str(has_at), title, content])) )
		num += 1
	except Exception:
		print line,
		pass

_identifer.save(sys.argv[3])
print "num: %d"%num
