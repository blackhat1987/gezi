#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   write-db.py
#        \author   chenghuige  
#          \date   2014-07-01 13:58:28.897098
#   \Description  
# ==============================================================================

import sys,os
import gezi #must before MySQLdb why...
import MySQLdb
 
conn = MySQLdb.connect(host='10.36.99.18',user='root',passwd='root',db='tieba',port=3316)
sql = "delete from dm_monitor where monitor_type = 20070"

monitor_type = '20070'

cur = conn.cursor()
cur.execute('set names gbk')
cur.execute(sql)
conn.commit()
cur.close()
