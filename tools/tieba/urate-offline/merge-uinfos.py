#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   merge-uinfos.py
#        \author   chenghuige  
#          \date   2015-03-25 19:00:23.362218
#   \Description  
# ==============================================================================

import sys,os
import time,datetime

l = time.localtime()
d1 = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = 1)).strftime('%Y%m%d')
d2 = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = 2)).strftime('%Y%m%d')
d3 = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = 3)).strftime('%Y%m%d')
d4 = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = 4)).strftime('%Y%m%d')
d5 = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = 5)).strftime('%Y%m%d')
d6 = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = 6)).strftime('%Y%m%d')
d7 = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = 7)).strftime('%Y%m%d')
d8 = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = 8)).strftime('%Y%m%d')

os.system('hive -f ./merge-uinfos.hql -hiveconf d1=%s d2=%s d3=%s d4=%s d5=%s d6=%s d7=%s d8=%s'%(d1,d2,d3,d4,d5,d6,d7,d8)) 
