#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test-seg.py
#        \author   chenghuige  
#          \date   2014-03-01 13:32:30.259515
#   \Description  
# ==============================================================================

import sys,os
import mysql_urate
from libgezi import *

LogHelper.set_level(4)

seg_init()

fs = FeatureSelector()
out = open(sys.argv[2],'w')
conn, cur = mysql_urate.urate_db()
for line in open(sys.argv[1]):
	try:
		l = line.strip().split('\t')
		pid = l[0]
		label = l[1]
		nresult = cur.execute('select title, content from instances where post_id=%s'%pid)
		results = cur.fetchmany(nresult)
		out.write('%s\t%s\t%s\n'%(label,results[0][0],results[0][1]))
		vec = StrVec()
		segment(results[0][0], vec)
		segment(results[0][1], vec)
		fs.add(vec, int(label))
	except Exception:
		print line,
		continue

fs.method(CHI)
fs.strategy(FeatureSelector.AVG)
fs.calc()
fs.show()
	
