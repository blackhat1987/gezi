#!/usr/bin/env python
import sys,os
null = '\N'
freq = 1
seg_sep = '$#$'
sep = '\t'
for line in sys.stdin:
	try:
		#[class_, words_] = line.strip().split(sep)
		#len_ = str(len(line.strip().split(sep)))
		#print sep.join([len_, len_, len_])
		#print '%s|\t%d|\t%d'%(line.strip().replace('\t','***'), line.strip().find('\x01'), line.strip().find('\t'))
		l = line.strip().split(sep)
		print sep.join([l[0], l[1], 'abc']) 
		continue
		if len(words_.strip()) < 1:
			continue
		words = words_.split(seg_sep)
		s = set()
		for word in words:
			if (len(word) > 0):
				s.add(word) 
		for word in s:
			if word == null:
				continue
			freq_ = str(freq)
			print sep.join([class_, word, freq_])
			print sep.join([null, word, freq_])
			print sep.join([class_, null, freq_])
		print sep.join([null, null, freq_])
	except Exception:
		continue
 
