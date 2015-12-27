#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   single_thread.py
#        \author   chenghuige  
#          \date   2015-12-25 09:55:12.101921
#   \Description  
# ==============================================================================

import sys,os 
import nowarning
import libtrate
import threading
from libsegment import Segmentor
Segmentor.Init()

num_threads = 4

from text_predictor import TextPredictor
predictor = TextPredictor('./ltrate.thread.model/identifer.bin', './ltrate.thread.model/')

lines = open(sys.argv[1]).readlines()
lines = lines[:50000]
block_size = len(lines) / num_threads

def run(lines, start):
	global predictor, num_threads, block_size
	end = start + block_size
	if end > len(lines):
		end = len(lines)
	for i in xrange(start, end):
		l = lines[i].split('\t')
		score = predictor.predict(l[0], l[1])
		#print score 

#for line in lines:
#	l = line.split('\t')
#	score = predictor.predict(l[0], l[1])

workers = []
start = 0
for index in xrange(num_threads):
	t = threading.Thread(target = run, args=(lines, start,))
	t.start()
	workers.append(t)
	start += block_size

for t in workers:
	t.join()
 
