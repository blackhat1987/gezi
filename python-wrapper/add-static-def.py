#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   add-static-def.py
#        \author   chenghuige  
#          \date   2014-04-17 11:47:27.547848
#   \Description  
# ==============================================================================

import sys,os

l = []
print '#define private public'
print '#define protected public'
for line in open(sys.argv[1]):
	print line,
	if (line.startswith('#include')):
		file_ = line.split()[1].strip('"')
		os.system('fix-static.py %s > %s'%(file_,'temp.static'))
		for def_ in open('temp.static').readlines():
			if def_.find('global') >= 0:
				pass
				def_=def_[:def_.find(';')]
				def_ = def_.split()[-1]
				var_ = def_.split('::')[-1]
				result = 'boost::python::scope().attr("%s") = %s;'%(var_, def_)
				l.append(result)	
			else:
				print def_,
	if (line.find('BOOST_PYTHON_MODULE') >= 0):
		for def_ in l:
			print def_

os.remove('temp.static')
	

 
