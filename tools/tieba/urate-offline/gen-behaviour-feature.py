#!/usr/bin/env python
#coding=gbk
# ==============================================================================
#          \file   gen-behaviour-feature.py
#        \author   chenghuige  
#          \date   2015-03-04 22:15:43.586237
#   \Description  
# ==============================================================================

import sys,os
sys.path.append('./')
from gezi import *

sep = '\t'

#@TODO collect_list() so you can track how many view command user used
for line in sys.stdin:
	#try:
		uid, pc_commands, wap_commands = line.rstrip('\n').split(sep)
		fe = FeatureVector()
		fe.add_section('behav')
		has_pc_commands = (pc_commands != 'null')
		has_wap_commans = (wap_commands != 'null')
	
		pc_commands = pc_commands[1:-1].split(',')
		wap_commands = wap_commands[1:-1].split(',')

		has_pc_commit = False
		has_wap_commit = False 

		for item in pc_commands:
			if item.endswith('thread/add"') or item.endswith('post/add"'):
				has_pc_commit = True

		for item in wap_commands:
			if item.endswith('thread/add"') or item.endswith('post/add"'):
				has_wap_commit = True

		pc_commands_length = len(pc_commands)
		wap_commands_length = len(wap_commands)

		fe.add(has_pc_commands, 'has_pc_commands')
		fe.add(has_wap_commans, 'has_wap_commans')
		fe.add(has_pc_commit, 'has_pc_commit')
		fe.add(has_wap_commit, 'has_wap_commit')
		fe.add(pc_commands_length, 'pc_commands_length')
		fe.add(wap_commands_length, 'wap_commands_length')

		print sep.join([uid, str(fe.Length()), fe.str(), fe.Str(), ','.join(fe.names()), str(int(has_pc_commit)), str(int(has_wap_commit))])
	#except Exception:
	#	continue
 
