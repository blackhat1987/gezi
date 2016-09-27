#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   merge-urate-behaviour-feature.py
#        \author   chenghuige  
#          \date   2015-03-04 23:10:23.889718
#   \Description  
# ==============================================================================

import sys,os
sys.path.append('./')

from gezi import *

sep = '\t'
for line in sys.stdin:
	#try:
		uid, feature, feature_names, feature2, feature_names2 = line.rstrip('\n').split(sep)

		fe = merge_feature(feature, feature_names, 'oldPcBehav', feature2, feature_names2)

		print sep.join([uid, str(fe.Length()), fe.str(), fe.Str(), ','.join(fe.names())])

	#except Exception:
	#	continue

 
