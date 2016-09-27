#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   fix-pyplusplus-stl.py
#        \author   chenghuige  
#          \date   2014-10-03 14:25:12.388520
#   \Description  
# ==============================================================================

import sys,os

def fix_stl(line):
	if line.strip().startswith('//'):
		return line
	pattern = 'bp::vector_indexing_suite<'
	pos = line.find(pattern)
	if pos >= 0:
		pos += len(pattern) 
		pos2 = line.rfind('>')
		line2 = line[pos : pos2]
		pos3 = line2.rfind(',')
		line2 = line2[0 : pos3]
		name = line2.strip() 
		return line.strip()[:-1] + '\n' + 'VEC_METHOD(%s)'%name + ";\n"
	else:
		return line

for line in open(sys.argv[1]):
	print fix_stl(line),
 
