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

predictor = PredictorFactory.LoadPredictor('./model')

vectors = liblego_predict.Vectors()
for line in open(sys.argv[1]):
	fe_str = line.split(';')[1]
	fe = Vector(fe_str, indexOnly = True)
	vectors.push_back(fe)

print vectors.size()
scores = liblego_predict.dvec(vectors.size(), 0)

for i in xrange(len(vectors)):
	scores[i] = predictor.Predict(vectors[i])

print scores[0]
print scores[1]
print scores[2]

