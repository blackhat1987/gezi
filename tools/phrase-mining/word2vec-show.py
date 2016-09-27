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


def show_result(model, word):
	print 'input word is: ', word
	for item in model.most_similar(positive=[word], topn=10):
		print item[0], item[1]

def show_result2(model, word, word1, word2):
	print 'input word is: ', word, '+',word1,'-',word2
	for item in model.most_similar(positive=[word, word1], negative=[word2], topn=10):
		print item[0], item[1]


model = gensim.models.Word2Vec.load('./word2vec.model')

#show_result(model, 'qq')
#show_result(model, '微信')
#show_result(model, '加v')
#show_result(model, '师妹')
#show_result(model, '色狼')
#show_result(model, '百度')
#show_result(model, '游泳')
#show_result(model, '刘亦菲')
#show_result(model, '博尔特')
show_result(model, '师妹')
show_result(model, '扣扣')
show_result(model, '周杰伦')
show_result(model, '库里')
show_result2(model, '苹果', '乔布斯','香蕉')
show_result2(model, '苹果', '香蕉','乔布斯')

show_result(model, '很好')
show_result(model, '操蛋')
show_result(model, '骚女')


