#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-content.py
#        \author   chenghuige  
#          \date   2015-08-05 11:50:33.804809
#   \Description  
# ==============================================================================

import sys,os
import nowarning
from libtieba import *
from libstringutil import *
from libgezi import *

for line in open(sys.argv[1]):
	l = line.split('\t')
	if len(l) == 2:
		title = utf82gbk(l[0])
		content = strip_html(utf82gbk(l[1].strip()))
		isthread = is_thread(title)
		title = get_real_title(title) 

		title = normalize_str(title)
		content = normalize_str(content)
		if isthread:
			print title
			if len(content) > 0:
				print content 
		else:
			if len(content) > 0:
				print content
 
