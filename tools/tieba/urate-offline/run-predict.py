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
pre2 = None
pre_train = None
while(True):
	time.sleep(60)
	now = time.strftime('%Y%m%d',time.localtime(time.time())) 
	l = time.localtime()
	now_hour =  l[3]

	if now != pre and now_hour >= 2  and now_hour <= 20:
		print 'run %s'%now 
                last_day = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = 1)).strftime('%Y%m%d')
		del_day = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = 10)).strftime('%Y%m%d')
		len_ = 0
                try:
                    len_ = len(open('./uinfo.%s.txt'%last_day).readlines()) 
                except Exception:
                    len_ = 0
		if len_ > 10 and len_ < 250000:
                    continue
		os.system('sh predict.sh %s'%(last_day))
		os.system('rm -rf ./uinfo.%s.txt'%(del_day))
		os.system('./write-db.py ./uinfo.%s.txt 0.995 10000'%(last_day))
                try:
		    len_ = len(open('./uinfo.%s.txt'%last_day).readlines())
                except Exception:
                    len_ = 0
		if len_ > 10 and len_ < 250000:
			pre = now
	



 
