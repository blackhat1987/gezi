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
from libmelt_predict import Vector, Predictor, PredictorFactory


predictor = PredictorFactory.LoadPredictor('./model')

fe = Vector('37:0.0769231,250:0.333333,3152:0.5,24927:1,44234:1,69028:0.0769231,69241:0.25,72143:0.5,93918:1,113225:0.4')
print predictor.Predict(fe)

fe = Vector('45:0.166667	55:0.166667	66:0.111111	67:0.0714286	191:0.125	328:0.0909091	331:0.25	793:0.333333	887:0.166667	948:0.25	1685:0.5	4622:0.571429')
print predictor.Predict(fe)