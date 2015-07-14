#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   sort.py
#        \author   chenghuige  
#          \date   2014-04-25 18:12:38.716273
#   \Description  
# ==============================================================================

import sys,os
from gflags import *
import gflags
DEFINE_string('sep', '\t', 'seprator')
DEFINE_boolean('reverse', True, 'sort reverse?')
DEFINE_boolean('header', False, '')

try:
  sys.argv = FLAGS(sys.argv)  # parse flags
except gflags.FlagsError, e:
  print '%s\nUsage: %s ARGS\n%s' % (e, sys.argv[0], FLAGS)
  sys.exit(1)

col = int(sys.argv[2])
li = []
for line in open(sys.argv[1]):
	if FLAGS.header:
		FLAGS.header = False 
		print line,
	else:
		try:
			l = line.rstrip().split(FLAGS.sep)
			li.append((float(l[col]), line.rstrip()))
		except Exception:
			print line
			print l[col]
			exit(1)
			

li.sort(reverse = FLAGS.reverse)

for item in li:
	print item[1]

