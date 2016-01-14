#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test.py
#        \author   chenghuige  
#          \date   2016-01-07 17:36:53.844079
#   \Description  
# ==============================================================================

import sys,os

import nowarning
from liblego_predict import Vector, Predictor, PredictorFactory
import liblego_predict

liblego_predict.set_num_threads(24)
#print 'num_thread:', liblego_predict.get_num_threads()

predictor = PredictorFactory.LoadPredictor('./model')


vectors = liblego_predict.Vectors()
for line in open(sys.argv[1]):
	fe_str = line.split(';')[1]
	fe = Vector(fe_str, indexOnly = True)
	vectors.push_back(fe)

scores = predictor.BulkPredict(vectors)

for score in scores:
	print score

