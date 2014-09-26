#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   fullposts-predict.py
#        \author   chenghuige  
#          \date   2014-09-23 08:46:11.764929
#   \Description  
# ==============================================================================

import sys,os

tid = sys.argv[1]
out = open('temp.txt', 'w')
out.write('%s\t%s\n'%(tid, '1'))

os.system('./fullposts_train -i temp.txt')


 
