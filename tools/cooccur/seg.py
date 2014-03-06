#!/usr/bin/env python
# ==============================================================================
#          \file   seg.py
#        \author   chenghuige  
#          \date   2014-03-01 13:32:30.259515
#   \Description  
# ==============================================================================

import sys,os
from libgezi import *

LogHelper.set_level(4)

data_path = 'data.tar.gz/wordseg'
type_ = 0
conf_path = 'conf.tar.gz/scw.conf'
seg_init2(data_path, type_, conf_path)

sep = '\t'
sep_seg = '$#$'
for line in sys.stdin:
	try:
		print sep.join([line.strip(), '1'])
		l = line.strip().split(sep)
		label = l[0]
		title = l[3] 
		content = l[4]
		result = ''
		if is_thread(title):
			result += segment2(title, sep_seg)
			result += sep_seg
		content = strip_html(content)
		result += segment2(content, sep_seg)
		print sep.join([label, result])
	except Exception:
		continue

