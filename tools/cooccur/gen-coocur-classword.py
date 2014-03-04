#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-coocur-classword.py
#        \author   chenghuige  
#          \date   2014-03-04 14:45:34.365596
#   \Description  
# ==============================================================================

import sys,os

null = '\N'
freq = 1
for line in open(sys.argv[1]):
	try:
		[class_, words_] = line.strip().split('\x01')
		if len(words_.strip()) < 1:
			continue
		words = words_.split('\t')
		s = set()
		for word in words:
			s.add(word) 
		for word in s:
			if word == null:
				continue
			print '%s\t%s\x01%d'%(class_, word, freq)
			print '%s\t%s\x01%d'%(null, word, freq)
			print '%s\t%s\x01%d'%(class_, null, freq)
		print '%s\t%s\x01%d'%(null, null, freq)
	except Exception:
		continue
 
