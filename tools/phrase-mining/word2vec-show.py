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
#show_result(model, '΢��')
#show_result(model, '��v')
#show_result(model, 'ʦ��')
#show_result(model, 'ɫ��')
#show_result(model, '�ٶ�')
#show_result(model, '��Ӿ')
#show_result(model, '�����')
#show_result(model, '������')
show_result(model, 'ʦ��')
show_result(model, '�ۿ�')
show_result(model, '�ܽ���')
show_result(model, '����')
show_result2(model, 'ƻ��', '�ǲ�˹','�㽶')
show_result2(model, 'ƻ��', '�㽶','�ǲ�˹')

show_result(model, '�ܺ�')
show_result(model, '�ٵ�')
show_result(model, 'ɧŮ')


