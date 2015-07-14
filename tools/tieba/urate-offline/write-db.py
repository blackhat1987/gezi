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
sql = "insert ignore into dm_monitor(monitor_type, title, content, user, forum, user_id) values (%s, %s, %s, %s, %s, %s)"

monitor_type = '20012'

thre = float(sys.argv[2])

thre2 = 0
if len(sys.argv) > 3:
  thre2 = float(sys.argv[3])


def get_len(file_):
    count = 0
    for line in open(sys.argv[1]):
        uid, user_name, score, post_id, forum_name, title, content, feature_len, feature = line.rstrip('\n').split('\t')
        if content > 1000:
            content = content[:1000]
        content = content.replace('"','')
        title = title.replace('"','')
        val = [monitor_type, str(count) + ' ' + score + ' ' + gezi.to_gbk(title), gezi.to_gbk(content), gezi.to_gbk(user_name), gezi.to_gbk(forum_name), uid]
        score = float(score)
        if len(title.split('#')) < 2:
            continue 
        count += 1
        if thre > 1: 
            if count > thre:
                break
        else:
            if score < thre:
                break
        if thre2 != 0:
            if thre2 > 1: 
                if count > thre2:
                    break
        else:
            if score < thre2:
                break
    return count

len_ = get_len(sys.argv[1])
len_ -= 1
print len_
if len_ < thre or len_ < thre2:
    print 'error data: ',len_ 
    exit(1)

vals=[]
count = 0
for line in open(sys.argv[1]):
  uid, user_name, score, post_id, forum_name, title, content, feature_len, feature = line.rstrip('\n').split('\t')
  if content > 1000:
    content = content[:1000]
  content = content.replace('"','')
  title = title.replace('"','')
  val = [monitor_type, str(count) + ' ' + score + ' ' + gezi.to_gbk(title), gezi.to_gbk(content), gezi.to_gbk(user_name), gezi.to_gbk(forum_name), uid]
  score = float(score)
  if len(title.split('#')) < 2:
    continue 
  count += 1
  if thre > 1: 
    if count > thre:
      break
  else:
    if score < thre:
      break
  if thre2 != 0:
    if thre2 > 1: 
      if count > thre2:
        break
    else:
      if score < thre2:
        break
  vals.append(val)
  if len(vals) >= 50:
    cur = conn.cursor()
    cur.execute('set names gbk')
    try:
      print 'writting to db count: ' + str(len(vals))
      cur.executemany(sql, tuple(vals))
    except Exception, e:
      for val in vals:
        val[3] = ''
      try:
        cur.executemany(sql, tuple(vals))
      except Exception, e:
        print e
    conn.commit()
    cur.close()
    vals = []

if len(vals) > 0:
  cur = conn.cursor()
  cur.execute('set names gbk')
  try:
    print 'writting to db count: ' + str(len(vals))
    cur.executemany(sql, tuple(vals))
  except Exception, e:
    print e
  conn.commit()
  cur.close()
  vals = []

