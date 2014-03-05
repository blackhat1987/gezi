#!/usr/bin/env python
import sys,os
null = '\N'
freq = 1
sep = '\t'
seg_sep = '$#$'
for line in sys.stdin:
	try:
		class_, words_ = line.strip().split(sep)
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
 
