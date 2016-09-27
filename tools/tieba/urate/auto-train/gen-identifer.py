#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-identifer.py
#        \author   chenghuige  
#          \date   2014-05-04 20:12:59.911103
#   \Description  
# ==============================================================================

import sys,os

import nowarning
from libgezi import *
from libidf import *
from gezi import *

LogHelper.set_level(4)
_identifer = Idf()

from trate_conf import *

def calc(l):
	vec = svec()
	li = get_words(l, ngram, sep)
	get_skip_bigram(l, li, skip, sep)
	for item in li:
		vec.append(item)
	_identifer.add(vec)

def calc2(l, type):
	vec = svec()
	li = get_words(l, ngram)
	get_skip_bigram(l, li, skip, sep)
	for item in li:
		vec.append(item + sep + type)
	_identifer.add(vec)

num = 0
for line in open(sys.argv[1]):
	num += 1
	if num % 1000 == 0:
		print num 
	pid,label, has_pic, has_url, has_num, has_at, title, content = line.rstrip('\n').split('\t')

	has_pic = has_url = has_at = '0'

	l1 = title.split(sep)
	calc(l1)

	l = content.split(sep)
	calc(l)

	l = l1 + l
	l = l[:20]
	if (has_pic == '1'):
		calc2(l, '<pic>')

	if (has_url == '1'):
		calc2(l, '<url>')

	#if (has_num == '1'):
	#	calc2(l, '<num>')

	if (has_at == '1'):
		calc2(l, '<at>')

_identifer.save(sys.argv[2]) 
