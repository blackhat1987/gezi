#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   word2vec.py
#        \author   chenghuige  
#          \date   2015-08-21 19:04:53.853856
#   \Description  
# ==============================================================================

import sys,os

import gensim
import  logging
logging.basicConfig(format='%(asctime)s : %(levelname)s : %(message)s', level=logging.INFO)

import nowarning
from libsegment import *


Segmentor.SetStrategy(SEG_USE_POSTAG)
Segmentor.Init()

class MySentence(object):
	def __init__(self, filename):
		self.filename = filename 

	def __iter__(self):
		for line in open(self.filename):
			l = [item.strip() for item in Segmentor.Segment(line.strip(), SEG_MERGE_NEWWORD) if len(item.strip()) > 0] 
			yield l 

sentences = MySentence(sys.argv[1])

model = gensim.models.Word2Vec(sentences, workers = 20)

model.save('word2vec.model')

for item in model.vocab:
	print item, len(item)
for item in model.most_similar(positive=['我们'], topn=5):
	print item[0], item[1]
