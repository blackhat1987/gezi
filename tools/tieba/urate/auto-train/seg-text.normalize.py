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
Segmentor.init()
seg = Segmentor()
print seg.segment('我的扣扣是', '|', SEG_BASIC)
total = len(open(sys.argv[1]).readlines())
print 'total: %d'%total 
_pb = ProgressBar(total)
_identifer = Idf()
out = open(sys.argv[2], 'w')
num = 0
for line in open(sys.argv[1]):
	_pb.progress(num)
	try:
		pid, label, title, content = line.strip().split('\t')
		title = get_real_title(title)
		tvec = seg.segment(title, SEG_BASIC)
		_identifer.add(tvec)
		title = '$#$'.join(tvec)
		print content, contains_url(content), contains_pic(content)
		content = strip_html(content)
		#content = normalize_str(content)
		cvec = seg.segment(content, SEG_BASIC)
		_identifer.add(cvec)
		content = '$#$'.join(cvec)
		out.write( '%s\n'%('\t'.join([pid, label, title, content])) )
		num += 1
	except Exception:
		pass

_identifer.save(sys.argv[3])
print "num: %d"%num
