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

import gezi 

pids = {}
titles = {}
for line in open(sys.argv[1]):
	pid, label = line.rstrip().split('\t')

	if pid in pids:
		continue

	pids[pid] = 1

	if os.path.exists('./history/%s.json'%pid):
		try:
			obj = gezi.jsonfile2obj('./history/%s.json'%pid)
			title = obj.nowPostInfo.title.encode('gbk').replace('\n', ' ')
			content = obj.nowPostInfo.content.encode('gbk').replace('\n', ' ')
			print '\t'.join([pid, label, title, content]) 
			continue
		except Exception:
			pass

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
	#title2 = title
	#if len(title2) > 10:
	#	title2 = title2[6:-6]
	#if not title2 in titles:
	#	titles[title2] = 1
	print '\t'.join([pid, label, title, content]) 
