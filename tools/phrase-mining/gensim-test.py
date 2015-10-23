#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gensim.py
#        \author   chenghuige  
#          \date   2015-08-21 19:41:01.236075
#   \Description  
# ==============================================================================

import sys,os

import gensim
sentences = [['first', 'sentence'], ['second', 'sentence']]
model = gensim.models.Word2Vec(sentences, min_count=1)

