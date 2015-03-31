#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-user-grade-info.py
#        \author   chenghuige  
#          \date   2015-03-11 01:41:07.741467
#   \Description  
# ==============================================================================

import sys,os
sys.path.append('./')
import gezi 

sep = '\t'
for line in sys.stdin:
	uid, flag, level, score = line.rstrip('\n').split(sep)
	fe = gezi.FeatureVector()
	fe.add_section('ugrade')
	fe.add(int(flag), 'flag')
	fe.add(int(level), 'level')
	fe.add(int(score), 'score')

	print sep.join([uid, str(fe.Length()), fe.str(), fe.Str(), ','.join(fe.names())])
	
