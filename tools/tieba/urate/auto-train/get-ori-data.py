#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   get-ori-data.py
#        \author   chenghuige  
#          \date   2014-11-26 17:32:48.551571
#   \Description  
# ==============================================================================

import sys,os

path = "ftp://cp01-forum0015.cp01.baidu.com//home/forum/sifa/data/"

thread_spam = "%s/thread_spampid.txt"%path
thread_normal = "%s/thread_normalpid.txt"%path
thread_pv_spam = "%s/frs_spampid.txt"%path
thread_pv_normal = "%s/frs_normalpid.txt"%path

reply_spam = "%s/reply_spampid.txt"%path
reply_normal = "%s/reply_normalpid.txt"%path
reply_pv_spam = "%s/pb_spampid.txt"%path
reply_pv_normal = "%s/pb_normalpid.txt"%path

os.system('rm thread_spampid.txt')
os.system('rm thread_normalpid.txt')
os.system('rm frs_spampid.txt')
os.system('rm frs_normalpid.txt')
os.system('rm pb_spampid.txt')
os.system('rm pb_normalpid.txt')

command = 'wget %s .'%thread_spam
os.system(command)

command = 'wget %s .'%thread_normal
os.system(command)

command = 'wget %s .'%thread_pv_normal
os.system(command)

command = 'wget %s .'%thread_pv_spam
os.system(command)

command = 'wget %s .'%reply_spam
os.system(command)

command = 'wget %s .'%reply_normal
os.system(command)
 
command = 'wget %s .'%reply_pv_spam
os.system(command)

command = 'wget %s .'%reply_pv_normal
os.system(command)
