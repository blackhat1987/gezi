#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   predict.py
#        \author   chenghuige  
#          \date   2015-03-05 17:52:52.562756
#   \Description  
# ==============================================================================

import sys,os
sys.path.append('./')
from gezi import * 

predictor = PredictorFactory.LoadPredictor('./model/')
sep = '\t'
for line in sys.stdin:
	l = line.rstrip('\n').split(sep)
	feature = l[-1]
	fe = Vector(feature)
	score = predictor.Predict(fe)
	l[2] = str(score)
	print sep.join(l)
 
