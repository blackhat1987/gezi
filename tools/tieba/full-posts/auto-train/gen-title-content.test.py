#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-title-content.py
#        \author   chenghuige  
#          \date   2014-05-21 17:31:30.584101
#   \Description  
# ==============================================================================

import sys,os
import urllib,json

pids = {}
for line in open(sys.argv[1]):
	pid = line.strip()
	label = '1'
	if pid in pids:
		continue

	pids[pid] = 1

	url = "http://service.tieba.baidu.com/service/post?method=getPostInfo&post_ids=a:1:{i:0;i:%s;}&format=mcpackraw"%pid
	content = urllib.urlopen(url).readline().decode('gbk')	
	m = {}
	
	try:
	    m = json.loads(content)['output'][0]
	except Exception:
	    print "wrong [%s]"%pid
	    print content
	    print line
	    continue
	
	title = m['title'].encode('gbk').replace('\n', ' ')
	content = m['content'].encode('gbk').replace('\n', ' ')
	print '\t'.join([pid, label, title, content]) 
