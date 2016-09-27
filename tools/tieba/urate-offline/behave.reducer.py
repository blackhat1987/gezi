#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   self-recall.reducer.py
#        \author   chenghuige  
#          \date   2015-02-25 16:46:34.816350
#   \Description  
# ==============================================================================

import sys,os

def deal(li):
	command_set = set()
	if len(li) == 0 or len(li[0]) == 0:
		return 
	uid = li[0][0]
	for l in li:
		if len(l) == 0:
			continue
		command = l[-1]
		command_set.add(command.strip())
	#print uid + '\t' + ','.join(list(command_set))
 	if len(command_set) == 1:
		if 'thread/add' in command_set:
			print uid + '\t' + 'thread'
		elif 'post/add' in command_set:
			print uid + '\t' + 'post'
	elif len(command_set) == 2:
		if 'account/listmsg' in command_set:
			if 'thread/add' in command_set:
				print uid + '\t' + 'thread+msg'
			elif 'post/add' in command_set:
				print uid + '\t' + 'post+msg'
	

pre_word = None
li = []
sep = '\t'
for line in sys.stdin:
	try:
		l = line.rstrip().split(sep)
		if len(l) ==0 or len(l[0]) == 0:
			continue
		word = l[0]
		try:
			t = int(word)
		except Exception:
			continue
		if word != pre_word:
			if pre_word != None:
				deal(li)
				#print pre_word + '\t' + str(len(li))
				li = []
			pre_word = word 
		if len(li) < 1000:
			li.append(l)
	except Exception:
		continue

try:
	deal(li)
except Exception:
	pass
