#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   test.py
#        \author   chenghuige  
#          \date   2014-11-26 15:45:00.631614
#   \Description  
# ==============================================================================

import sys,os
from gflags import *

DEFINE_boolean('show', False, '')

def main(argv):
	try:
		argv = FLAGS(argv)  # parse flags
	except gflags.FlagsError, e:
		print '%s\nUsage: %s ARGS\n%s' % (e, sys.argv[0], FLAGS)
		sys.exit(1)
	
if __name__ == "__main__":  
	 main(sys.argv)  

 
