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

import nowarning 
from libtieba import *

import gezi 

pid_label = {}
pids = []
for line in open(sys.argv[1]):
	pid, label = line.rstrip().split('\t')
	pid_label[pid] = label
	pids.append(int(pid))

vec = ulvec()
gezi.list2vec(pids, vec)

m = get_posts_info_map(vec)
for item in m:
	pid = str(item.key())
	label = pid_label[pid]
	title = item.data().title.replace('\n', ' ')
	content = item.data().content.replace('\n', ' ')
	print '\t'.join([pid, label, title, content]) 
