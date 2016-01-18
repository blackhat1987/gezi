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
from collections import defaultdict 

import nowarning 
from gezi import *  #@FIXME gezi must import at last
import gezi
from libgezi import *
from libidentifer import *

LogHelper.set_level(4)
_identifer = DoubleIdentifer()
_identifer.load(sys.argv[2])
print 'load Identifer ok'
out = open(sys.argv[3], 'w')
word_num = _identifer.size()

from trate_conf import *

num = 0
for line in open(sys.argv[1]):
		if num % 1000 == 0:
			print num 
	#try:
		pid,label, has_pic, has_url, has_num, has_at, title, content = line.rstrip('\n').split('\t')
		has_pic = has_url = has_at = has_num = '0'
		pid = '_' + pid
		#tmap = defaultdict(float)
		words = []
		l1 = title.split(sep)
		li = gezi.get_words(l1, ngram)
		gezi.get_skip_bigram(l1, li, skip, sep)
		for word in li:
			id_ = _identifer.id(word)
			if id_ >= 0 :
				#tmap[id_] += _identifer.value(id_)
				words.append(str(id_))

		l = content.split(sep)
		li = gezi.get_words(l, ngram)
		gezi.get_skip_bigram(l, li, skip, sep)
		for word in li:
			id_ = _identifer.id(word) 
			if id_ >= 0:
				id = id_ + word_num
				#tmap[id] += _identifer.value(id_)
				words.append(str(id))

		l = [pid, label, str(word_num * 2)]
		l += words
		out.write( '%s\n'%('\t'.join(l)))
		num += 1
	#except Exception:
	#	print line,
	#	pass

print "num: %d"%num
