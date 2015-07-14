#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-text-feature.py
#        \author   chenghuige  
#          \date   2014-03-08 17:01:57.385278
#   \Description  input is seged text with (pid, title, content) output is sparse text feature 
#                 as described in tlc readme
# ==============================================================================

import sys, os
from gezi import *
from collections import defaultdict

LogHelper.set_level(4)
_identifer = DoubleIdentifer()
_identifer.load(sys.argv[2])
print 'load Identifer ok'
out = open(sys.argv[3], 'w')
word_num = _identifer.size()

ngram = 3
sep = '$#$'

num = 0
for line in open(sys.argv[1]):
		if num % 1000 == 0:
			print num 
	#try:
		pid,label, has_pic, has_url, has_num, has_at, title, content = line.rstrip('\n').split('\t')
		has_pic = has_url = has_at = has_num = '0'
		pid = '_' + pid
		tmap = defaultdict(float)
		l1 = title.split(sep)
		li = get_words(l1, ngram)
		get_skip_bigram(l1, li, 2, sep)
		for word in li:
			id_ = _identifer.id(word)
			if id_ >= 0 :
				tmap[id_] += _identifer.value(id_)

		l = content.split(sep)
		li = get_words(l, ngram)
		get_skip_bigram(l, li, 2, sep)
		for word in li:
			id_ = _identifer.id(word) 
			if id_ >= 0:
				id = id_ + word_num
				tmap[id] += _identifer.value(id_)

		l = l1 + l
		l = l[:20]
		li = get_words(l, ngram)
		get_skip_bigram(l, li, 2, sep)

		if has_pic == '1':
			for word in li:
				id_ = _identifer.id(word + sep + '<pic>')
				if id_ >= 0:
					tmap[id_] += _identifer.value(id_)

		if has_url == '1':
			for word in li:
				id_ = _identifer.id(word + sep + '<url>')
				if id_ >= 0:
					tmap[id_] += _identifer.value(id_)

		#if has_num == '1':
		#	for word in li:
		#		id_ = _identifer.id(word + sep + '<num>')
		#		if id_ >= 0:
		#			tmap[id_] += _identifer.value(id_)
		
		if has_at == '1':
			for word in li:
				id_ = _identifer.id(word + sep + '<at>')
				if id_ >= 0:
					tmap[id_] += _identifer.value(id_)

		l = [pid, label, str(word_num * 2)]
		for key,value in sorted(tmap.items()):
			l.append('%d:%f'%(key, value))
		if (len(l) == 3):
			l.append('0:0')
		out.write( '%s\n'%('\t'.join(l)))
		num += 1
	#except Exception:
	#	print line,
	#	pass

print "num: %d"%num
