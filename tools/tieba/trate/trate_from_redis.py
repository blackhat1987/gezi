#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   trate_from_redis.py
#        \author   chenghuige  
#          \date   2015-12-17 16:54:03.137910
#   \Description  
# ==============================================================================

import sys,os
import gflags

import nowarning
import libredis 
#from libgezi import LogHelper
libredis.LogHelper.set_level(4)


FLAGS = gflags.FLAGS

gflags.DEFINE_string('conf_file', 'redis_client.conf', '')
gflags.DEFINE_string('conf_dir', './conf', '')
gflags.DEFINE_string('thread_key', "#!thread!#", "")
gflags.DEFINE_integer('queue_size', 10, 'fetch num each time from redis')

pids = set()

redis_client = libredis.RedisClient()
ret = redis_client.Init(FLAGS.conf_file, FLAGS.conf_dir)

if ret != 0:
	print 'redis init fail ret:', ret
	exit(-1)

round = 0
while True:
	vec = libredis.svec()
	ret = redis_client.ZrangeFirstNElement(FLAGS.thread_key, FLAGS.queue_size, vec)
	if ret != 0:
		print 'read redis fail ret:', ret
	print len(vec)
	#vec.clear()
	num_old = 0
	num_new = 0 
	for pid in vec:
		if pid in pids:
			num_old += 1
		else:
			num_new += 1
			pids.add(pid)
	print 'new:', num_new, ' old:', num_old, ' total:', len(pids)
	round += 1
 
