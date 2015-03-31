#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   deal.py
#        \author   chenghuige  
#          \date   2015-02-06 20:15:35.823425
#   \Description  
# ==============================================================================

import sys,os

os.system('rm ./post.result/*.crc')

for f in os.listdir('./post.result/'):
	f = './post.result/' + f
	for line in open(f):
		try:
			l = line.split('\x01')
			l[1] = l[1].decode('utf-8').encode('gbk', 'ignore')
			l[2] = l[2].decode('utf-8').encode('gbk', 'ignore')
			l[1] = l[1][10:-2]
			l[2] = l[2][12:-2]
			print '\t'.join(l)
		except Exception:
			#print line 
			pass
	
os.system('rm -rf ./post.result/')

