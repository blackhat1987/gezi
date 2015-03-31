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
	uid, feature_len, feature, feature_str = line.rstrip('\n').split(sep)
	fe = Vector(feature)
	score = predictor.Predict(fe)
	print sep.join([uid, str(score), feature_len, feature, feature_str])

 
