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

from trate_predictor import TextPredictor
predictor = TextPredictor('./ltrate.thread.model/identifer.bin', './ltrate.thread.model/')


lines = open(sys.argv[1]).readlines()
lines = lines[:50000]
for line in lines:
	l = line.split('\t')
	score = predictor.predict(l[0], l[1])
	#print score
 
