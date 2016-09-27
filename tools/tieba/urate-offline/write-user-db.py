#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   write-unlabel-db.py
#        \author   chenghuige  
#          \date   2014-07-01 13:58:28.897098
#   \Description  
# ==============================================================================

import sys,os
import gezi #must before MySQLdb why...
import MySQLdb,urllib,json

conn = MySQLdb.connect(host='127.0.0.1',user='root',passwd='',db='forum_model',port=3307)

sql = "insert ignore into sample_model_one2many(model_type,suid,sample_content,score,thread_id,post_id,user_id,user_name,user_ip,forum_id,forum_name,title,post_content,post_time,sample_status,sample_type) values (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)"

error_log = open('db_error.log', 'w')
vals=[]
count = 0
max_count = -1
if len(sys.argv) > 2:
	max_count = int(sys.argv[2])
for line in open(sys.argv[1]):
	count += 1
	if max_count > 0 and count > max_count:
		break
	suid, user_name, score, post_id, forum_name, title_, content_, feature = line.strip().split('\t')
        title = ''
	sample_content = user_name + ' -- ' + score + ' -- ' + forum_name + '\n' + title_ + '\n' + content_ 
	sample_status = '2'
	sample_type = '1'
	model_type = 5
	post_content = ''
	post_time = 0
	user_id = suid
	user_ip = ''
        thread_id = 0
        forum_id = 0
        forum_name =''
        score = 0
	val = [model_type, suid, sample_content, score, thread_id, post_id, user_id, user_name, user_ip, forum_id, forum_name, title, post_content, post_time, sample_status, sample_type]
        vals.append(val)
	if len(vals) > 50:
	    cur = conn.cursor()
	    cur.execute('set names utf8')
	    try:
		print 'writting to db count: ' + str(len(vals))
		cur.executemany(sql, tuple(vals))
	    except Exception, e:
		print e
		error_log.write(e)
		error_log.write('\n')
		cur.close()
		continue
	    conn.commit()
	    cur.close()
	    vals = []

if len(vals) > 0:
	cur = conn.cursor()
	cur.execute('set names utf8')
	try:
		print 'writting to db count: ' + str(len(vals))
		cur.executemany(sql, tuple(vals))
	except Exception, e:
		print e
		error_log.write(e)
		error_log.write('\n')
		exit(-1)
	conn.commit()
	cur.close()
	vals = []

conn.close()
