#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   c++11fix.py
#        \author   chenghuige  
#          \date   2014-04-16 16:19:59.330937
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
	line = line.strip()
	#org_line = line.replace('private:', 'public:').replace('protected:', 'public:')
	org_line = line
	if (line.startswith('/') or line.startswith('#') or line.startswith('*')):
		print org_line
		continue 
	end_idx = line.rfind(';')
	if (end_idx == -1):
		print org_line
		continue
	if (line.startswith('const static') or line.startswith('static')):
		print org_line
		continue
	
	#line = line[:end_idx] #comment里面不要同行出现)

	if (line.find('&&') >= 0):
		continue

	if (line.find('= default') >= 0):
		print line[:line.rfind('=')].strip() + ';'
		continue

	idx1 = line.rfind(')')
	idx2 = line.rfind('=')
	if (idx1 > idx2):
		print org_line
		continue
	if idx2 == -1:
		print org_line
		continue 
	line = line[:idx2]
	line = line.strip() + ';'
	print line


 
