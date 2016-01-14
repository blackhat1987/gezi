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


predictor = PredictorFactory.LoadPredictor('./model')

for line in open(sys.argv[1]):
	fe_str = line.split(';')[1]
	fe = Vector(fe_str, indexOnly = True)
	print predictor.Predict(fe)
