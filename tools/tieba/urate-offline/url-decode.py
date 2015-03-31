#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   url-decode.py
#        \author   chenghuige  
#          \date   2015-02-26 16:14:50.620137
#   \Description  
# ==============================================================================

import sys,os
import urllib

for line in sys.stdin:
	line = urllib.unquote(line)
	print line,


 
