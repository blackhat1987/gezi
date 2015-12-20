#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   trate_predictor.py
#        \author   chenghuige  
#          \date   2015-12-18 11:42:52.080763
#   \Description  
# ==============================================================================

import sys,os

import libmelt_predict as melt
#import libmelt_predict_debug as melt
import libgezi 
import libidentifer

class TextPredictor(object):
	def __init__(self, identifer_path, predictor_path):
		self.identifer = libidentifer.DoubleIdentifer()
		self.identifer.Load(identifer_path)

		pf = melt.PredictorFactory()
		self.predictor = pf.LoadPredictor(predictor_path)

	def deal_title(self, title):
		return title + ' ' + libgezi.normalize_str(title)

	def deal_content(self, content):
		content = libgezi.strip_html(content)
		if len(content) > 100:
			content = libgezi.gbk_substr(content, 0, 100)
		content = content + ' ' + libgezi.normalize_str(content)
		return content

	def predict(self, title, content):
		title = self.deal_title(title)
		content = self.deal_content(content)
		score = melt.TextPredictor.Predict(title, content, self.identifer, self.predictor)
		return score


