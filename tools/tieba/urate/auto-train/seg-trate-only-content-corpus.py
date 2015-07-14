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
out = open(sys.argv[3], 'w')
types = ["pic", "url", "num", "at"]
sep = '$#$'
num = 0

spam_contents = open(sys.argv[1]).readlines()
normal_contents = open(sys.argv[2]).readlines()

print len(spam_contents)
print len(normal_contents)

l = []
for i in range(len(spam_contents)):
	l.append(('1', '', spam_contents[i]))

for i in range(len(normal_contents)):
	l.append(('0', '', normal_contents[i]))

pid = 0
for item in l:
	_pb.progress(pid)
	label = item[0]
	title = item[1].strip()
	content = item[2].strip()
	#try:
	title = get_real_title(title).replace(':', ' ')
	tvec = Segmentor.Segment(title, SEG_BASIC)
	title = sep.join(tvec)
	src = title + " " + content 
	has_pic = int(contains_any(src, "pic"))
	has_url = int(contains_any(src, "url"))
	has_num = int(contains_any(src, "num"))
	has_at = int(contains_any(src, "at"))

	content = strip_html(content).replace(':', ' ')
	if len(content) > 100:
		content = gbk_substr(content, 0, 100)
	cvec = Segmentor.Segment(content, SEG_BASIC)
	content = sep.join(cvec)
	#out.write('%s |t %s|c %s\n'%(label, title, content))
	out.write( '%s\n'%('\t'.join(['_%d'%(pid), label, str(has_pic), str(has_url), str(has_num), str(has_at), title, content])) )
	pid += 1
	#except Exception:
	#	print item,
	#	pass

_identifer.save(sys.argv[4])
print "num: %d"%pid
