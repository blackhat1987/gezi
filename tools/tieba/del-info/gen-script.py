#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-script.py
#        \author   chenghuige  
#          \date   2015-06-09 13:57:27.397187
#   \Description  
# ==============================================================================

import sys,os
import time,datetime

code_begin = '''
set mapred.job.name=chenghuige.add; 
set hive.map.aggr=true; 
set hive.auto.convert.join=false; 
set mapred.job.map.capacity=6000; 
set mapred.job.reduce.capacity=5000;
set mapred.reduce.tasks = 1000;
USE queryPlatform;

DROP TABLE IF EXISTS gezi_del_info;
CREATE TABLE gezi_del_info AS 
SELECT * FROM (
SELECT L{0}.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = {0} and post_id % {1} == 0)L{0}
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = {0} and post_id % {1} == 0)R{0}
ON L{0}.post_id == R{0}.post_id 
'''
code_middle = '''UNION ALL
SELECT L{0}.post_id, uid, uname, thread_id, title, content, create_time, op_username, monitor_type
FROM 
(SELECT post_id, uid, uname, thread_id, get_json_object(title, "$.title") AS title, get_json_object(content, "$.content") AS content, create_time
FROM default.pbdata
WHERE day = {0} and post_id % {1} == 0)L{0}
LEFT OUTER JOIN 
(SELECT post_id, op_username, monitor_type
FROM default.forum_ueg_anti_monitor
WHERE day = {0} and post_id % {1} == 0)R{0}
ON L{0}.post_id == R{0}.post_id 
'''

code_end = ''')T;
'''

now = time.strftime('%Y%m%d',time.localtime(time.time())) 
l = time.localtime()
last_day = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = 1)).strftime('%Y%m%d')

days = int(sys.argv[1])

code = code_begin.format(last_day, days)
for i in range(2,days + 1):
    the_day = (datetime.date(l[0],l[1],l[2]) -  datetime.timedelta (days = i)).strftime('%Y%m%d')
    code += code_middle.format(the_day, days)

code += code_end

print code


 
 
