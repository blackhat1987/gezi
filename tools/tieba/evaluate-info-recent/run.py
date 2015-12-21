#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   run.py
#        \author   chenghuige  
#          \date   2015-02-26 17:48:25.559868
#   \Description  
# ==============================================================================

import sys,os
import time,datetime

pre = None
while(True):
	now = time.strftime('%Y%m%d',time.localtime(time.time())) 
	l = time.localtime()
	now_hour =  l[3]
	if now != pre and now_hour == 23:
		pre = now 
		print 'run %s'%now 
		os.system('sh ./get-recent.sh 6')
	time.sleep(60)



 
