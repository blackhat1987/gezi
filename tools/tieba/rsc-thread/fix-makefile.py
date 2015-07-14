#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   fix-makefile.py
#        \author   chenghuige  
#          \date   2014-09-18 10:24:01.649175
#   \Description  
# ==============================================================================

import sys,os

for line in open(sys.argv[1]):
    if ((not line.find('libcurl') >= 0) and (not line.find('libboost_log_setup.a') >= 0)):
        print line,

 
