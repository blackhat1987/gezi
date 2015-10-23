#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-dict.py
#        \author   chenghuige  
#          \date   2015-08-18 18:00:59.563094
#   \Description  
# ==============================================================================

import sys,os

from libsegment import *

Segmentor.Init()

set_ = set()
for line in open(sys.argv[1]):
	vec = Segmentor.Segment(line.strip())
	for phrase in vec:
		phrase = phrase.strip()
		if len(phrase) > 3 and len(phrase) < 20:
			set_.add(phrase)

out = open('dict.txt', 'w')
for phrase in set_:
	out.write('%s\n'%phrase)

 
