#!/usr/bin/env python

import sys 
sys.path.append('./')
import sets
import traceback
import time
import math
import re

import gezi

CMD_SET=sets.Set(['f/frs', 'add', 'thread/add', 'post/add', '20-0','panel', 'browse/comment/list','browse/picture/guide','browse/picture/toplist', 'replyme','jump','main', 'atme', 'get_forumlist', 'upload/pic', 'others', 'cm_click_pic','f/good', 'browse/photo/AlbumRecommend', 'post/delete', 'thread/delete', 'recycle', 'my_tie', 'forum', 'view_album', 'allfeed', 'fans', 'storethread', 'browse/photo/frsInfo', 'like/commit/notice/delete', 'like/commit/add', 'comment/comment'])
BR_CMD_SET=sets.Set(['f/frs', '20-0', 'browse/comment/list', 'browse/picture/guide', 'browse/picture/toplist','replyme','jump','main', 'atme', 'get_forumlist','f/good', 'browse/photo/AlbumRecommend','recycle', 'my_tie', 'forum', 'view_album', 'allfeed', 'fans','browse/photo/frsInfo'])
COMMIT_CMD_SET=sets.Set(['thread/add', 'post/add'])
UI_CMD_SET = sets.Set(['like/commit/notice/delete', 'like/commit/add', 'comment/comment'])

CMD_SET = CMD_SET.union(BR_CMD_SET).union(COMMIT_CMD_SET).union(UI_CMD_SET)

#class for a single behaviour record
class Item:
	pass

#get sequence feature map
def get_seq_map(path):
	f = open(path, 'r')
	index = 0
	seq_map = {}
	for line in f:
		s = line.strip().split("\t")
		if len(s) != 2:
			continue
		k = s[0]
		seq_map[k] = index
		index = index + 1
	f.close()

	return seq_map
		
# @brief: get the sequence feature
# @param item_list: user history record list
# @param findex_map: feature index map
# @param length: length of the sequence
def get_seq_feature(item_list, findex_map, length):

	clist = []
	ret = []
	for item in item_list:
		if item.error_no != 0:
			continue
		if item.command in CMD_SET:
				clist.append(item)	
	fcnt_map = {}
	for i in range(len(clist) - length + 1):
		key = ''
		for j in range(i, i + length, 1):
			key = key + "," + clist[j].command
		if findex_map.get(key) == None:
			continue
		else:
			if fcnt_map.get(key) == None:
				fcnt_map[key] = 1
			else:
				fcnt_map[key] = fcnt_map[key] + 1
	for k,v in findex_map.items():
		value=fcnt_map.get(k,0)
		ret.append([v,value])
#	for k,v in fcnt_map.items():
#		index = findex_map.get(k)
#		ret.append([index, v])
	ret.sort(lambda d1, d2 : d1[0] - d2[0])

	return ret


# @brief: get max freq in a time unit
# @param time_list: time list in unix timestamp
# @param unit: time unit
def get_max_freq(time_list, unit):
	if len(time_list) == 0:
		return 0
	time_list.sort()
	ret = 1
	for i in range(len(time_list) - 1, 0, -1):
		for j in range(i):
			if time_list[i] - time_list[j] <= unit:
				ret = max(ret, i - j + 1)
				break
	return ret	
	
	
# count distinct cookie cnt
def count_cookie(item_list):
	cookie_set = sets.Set([])
	for item in item_list:
		cookie_set.add(item.cookie)
	return len(cookie_set)

def count_IP_cookie(item_list):
		IP_cookie_set = sets.Set([])
		for item in item_list:
				ip_cookie = item.cookie + ":" +str(item.uip)
				IP_cookie_set.add(ip_cookie)
		return len(IP_cookie_set)

# count distinct uip cnt
def count_ip(item_list):
	ip_set = sets.Set([])
	for item in item_list:
		ip_set.add(item.uip)
	return len(ip_set)

# count distinct city cnt
def count_city(item_list):
	city_set = sets.Set([])
	for item in item_list:
		city_set.add(item.city)
	return len(city_set)

# count distinct forum cnt
def count_forum(item_list):
	forum_set = sets.Set([])
	for item in item_list:
		forum_set.add(item.fname)
	return len(forum_set)


# @brief: get the max frequency in a time unit for several commands
# @param item_list: user history
# @param command_set:  commands to count
# @param unit: time unit in seconds
# @retval: 
def get_command_max_freq(item_list, command_set, unit):
	time_list = []
	for item in item_list:
		if item.error_no == 0 and item.command in command_set:
			time_list.append(item.time)
	ret = get_max_freq(time_list, unit)

	return ret

def get_fail_max_freq(item_list, command_set, unit):
		time_list = []
		for item in item_list:
				if item.error_no > 0 and item.command in command_set:
						time_list.append(item.time)
		ret = get_max_freq(time_list, unit)

		return ret
# @brief: get the average frequency in a time unit for serveral commands
# @param item_list: 
# @param command_set:
# @param unit: 
# @retval: 
def get_command_avg_freq(item_list, command_set, unit):
	time_list = []
	for item in item_list:
		if item.error_no == 0 and item.command in command_set:
			time_list.append(item.time)
	time_list.sort()
	if len(time_list) < 2:
		return 0
	time_last = time_list[-1] - time_list[0]
	time_cnt = max(1, time_last / float(unit))

	return len(time_list) / time_cnt

def get_fail_avg_freq(item_list, command_set, unit):
		time_list = []
		for item in item_list:
				if item.error_no > 0 and item.command in command_set:
						time_list.append(item.time)
		time_list.sort()
		if len(time_list) <2 :
				return 0
		time_last = time_list[-1] - time_list[0]
		time_cnt = max(1, time_last / float(unit))
		return len(time_list)/time_cnt

# @brief: get the ratio of two command sets
# @param item_list: 
# @param command_set1: 
# @param command_set2: 
# @retval: 
def get_command_ratio(item_list, command_set1, command_set2):
	cnt1 = .0
	cnt2 = .0
	for item in item_list:
		if item.error_no != 0:
			continue
		if item.command in command_set1:
			cnt1 = cnt1 + 1
		elif item.command in command_set2:
			cnt2 = cnt2 + 1
	cnt1 = max(cnt1, 1.0)
	cnt2 = max(cnt2, 1.0)
	return cnt1 /cnt2

# @brief: get the max change frequency in a time unit
def get_change_freq(input, unit):
	input.sort(lambda d1, d2: d1[1] - d2[1])
	if len(input) > 5000:
		input = input[:5000]
	
	if len(input) <= 1:
		return 0
	ret = 0
	change = [0 for i in range(len(input))]
	for i in range(1, len(input), 1):
		if input[i][0] != input[i-1][0]:
			change[i] = change[i-1] + 1
		else:
			change[i] = change[i-1]
	for i in range(len(input) - 1, 0, -1):
		for j in range(i):
			if input[i][1] - input[j][1] <= unit:
				ret = max(ret, change[i] - change[j])
				break
		return ret
	
# return list for [cookie, time]
def get_cookie_time_list(item_list):
	ret = []
	for item in item_list:
		if item.error_no != 0:
			continue
		ret.append([item.cookie, item.time])
	return ret

def get_ip_time_list(item_list):
	ret = []
	for item in item_list:
		if item.error_no != 0:
			continue
		ret.append([item.uip, item.time])
	return ret

def get_city_time_list(item_list):
	ret = []
	for item in item_list:
		if item.error_no != 0:
			continue
		ret.append([item.city, item.time])
	return ret

def get_forum_time_list(item_list):
	ret = []
	for item in item_list:
		if item.error_no != 0 or item.fname.strip() == '' or item.fname == 'NULL':
			continue
		if item.command in COMMIT_CMD_SET:
			ret.append([item.fname, item.time])
	return ret

# get the ratio of failed commit
def get_fail_commit_ratio(item_list):
	cnt1 = .0
	cnt2 = .0
	for item in item_list:
		if item.command in COMMIT_CMD_SET:
			cnt2 = cnt2 + 1
			if item.error_no > 0:
				cnt1 = cnt1 + 1
	if cnt2 == 0:
		return 0
	return cnt1 / cnt2
	
# get the count of failed commit
def get_fail_commit_cnt(item_list):
	ret = 0
	for item in item_list:
		if item.command in COMMIT_CMD_SET:
			if item.error_no > 0:
				ret = ret + 1
	return ret

def get_quote_type_ratio(item_list):
		cnt1= .0
		cnt2= .0
		for item in item_list:
				if item.error_no==0 and item.command=='post/add':
						cnt2 = cnt2 + 1 
						if item.quote_type > 0:
								cnt1 =cnt1+1
		if cnt2 == 0:
				return 0
		return cnt1 / cnt2

def get_quote_type_cnt(item_list):
		ret = 0
		for item in item_list:
				if item.error_no==0 and item.command=='post/add':
						if item.quote_type > 0:
								ret = ret +1
		return ret

# get the active hours cnt
def get_hours(item_list):
	import time
	ret = 0
	hours = sets.Set([])
	for item in item_list:
		hour = time.localtime(item.time).tm_hour
		hours.add(hour)
	return len(hours)

# get the active minutes cnt
def get_minutes(item_list):
	ret = 0
	minutes = sets.Set([])
	for item in item_list:
		minute = time.localtime(item.time).tm_min
		minutes.add(minute)
	return len(minutes)

# get the ratio of active hours at night
def get_night_ratio(item_list):
	ret = 0.0
	if len(item_list) == 0:
		return 0
	for item in item_list:
		hour = time.localtime(item.time).tm_hour
		if hour in sets.Set([1,2,3,4,5,6]):
			ret = ret + 1
	return ret / len(item_list)

# get the thread and post commit ratio
def get_thread_post_ratio(item_list):
	ret = 0
	thread = 0
	post = 0
	for item in item_list:
		if item.command == 'thread/add':
			thread = thread + 1
		elif item.command == 'post/add':
			post = post + 1
	if post == 0:
		post = 1
	return thread / float(post)

# get the commit count with null refer
def get_post_null_refer_cnt(item_list):
	ret = 0
	for item in item_list:
		if item.command in COMMIT_CMD_SET and item.refer.strip() == '':
			ret = ret + 1
	return ret

def get_browse_null_refer_cnt(item_list):
	ret = 0
	for item in item_list:
		if item.command in BR_CMD_SET and item.refer.strip() == '' and item.is_pv == 1:
			ret = ret + 1
	return ret

# calculate entropy
def ent(l):
	ret = 0
	for p in l:
		if p == 0:
			p = 1e-9
		ret = ret + p * math.log(p, 2)
	if ret==0.0:
		return 0.0
	return -ret

# get the picture count
def get_pic_num(item_list):
	ret = 0
	for item in item_list:
		if item.command in COMMIT_CMD_SET:
			ret = ret + item.image_num
	return ret

# get the picture entropy
def get_pic_ent(item_list):
	p = []
	for item in item_list:
		if item.command in COMMIT_CMD_SET and item.image_num > 0:
			p.append(item.image_num)
			
	cnt = sum(p)
	for i in range(len(p)):
		p[i] = p[i] / float(cnt)
		
	return ent(p)

#get the post entropy
def get_post_ent(item_list):
	postdic={}
	count=0
	for item in item_list:
		if item.command in ['post/add','thread/add']:
			value=postdic.get(item.tid,0)+1
			postdic[item.tid]=value
			count+=1
	p=[]
	for (k,v) in postdic.items():
		p.append(v/float(count))
	if len(p)==0:
		return 0.0
	return ent(p)

def get_video_num(item_list):
	ret = 0
	for item in item_list:
		if item.command in COMMIT_CMD_SET:
			ret = ret + item.video_num
	return ret

def get_video_ent(item_list):
	ret = 0
	p = []
	for item in item_list:
		if item.command in COMMIT_CMD_SET and item.video_num > 0:
			p.append(item.video_num)
			
	cnt = sum(p)
	for i in range(len(p)):
		p[i] = p[i] / float(cnt)
		
	return ent(p)

# @brief: filter the wrong records
def get_valid_item_list(item_list):
	ret = []
	for item in item_list:
		if item.command in COMMIT_CMD_SET and item.error_no > 0:
			continue
		ret.append(item)
	return ret

def whether_is_numalpha(name_):
		if re.match('^[0-9a-zA-Z_]+$',name_):
				return 1
		else:
				return 0

def whether_is_purealpha(name_):
		if name_.isalpha():
				return 1
		else:
				return 0

def whether_is_numalpha2(name_):
		if re.match('^[a-zA-Z]+[0-9]+$',name_):
				return 1
		else:
				return 0

def whether_have_email_mobile(item_list):
		ret=0
		for item in item_list:
				if not item.email.strip()=='' or not item.mobile.strip()=='':
						ret = 1
						break
		return ret

def get_commit_forum_ratio(f_thread_add_freq_day,f_post_add_freq_day,f_forum_cnt):
		commit = f_thread_add_freq_day + f_post_add_freq_day
		if f_forum_cnt == 0:
				return .0
		ret = float(commit)/f_forum_cnt + float(f_forum_cnt)
		return ret

def whether_have_agent(item_list):
		ret=0
		for item in item_list:
				if not item.agent.strip()=='':
						ret = 1
						break
		return ret

def get_time_var(item_list, command_set):
		time_list=[]
		for item in item_list:
				if item.error_no == 0 and item.command in command_set:
						time_list.append(item.time)
		time_list.sort()
		if len(time_list) < 3:
				return 1866240000.0
		time_var_list = []
		for i in range(len(time_list)-1):
				x_time = time_list[i+1]-time_list[i]
				time_var_list.append(x_time)
		
		avg = float(sum(time_var_list))/len(time_var_list)
		var = .0
		for i in range(len(time_var_list)):
				var = var + (float(time_var_list[i])-avg)**2

		var = var / len(time_var_list)
		return var

def get_var(time_list, star ,end):
		time_list_var=[]
		for i in range(star , end ,1):
				x_time = time_list[i+1]-time_list[i]
				time_list_var.append(x_time)
		avg=float(sum(time_list_var))/len(time_list_var)
		var = .0
		for i in range(len(time_list_var)):
				var = var +float(time_list_var[i]-avg)**2
		var = var / len(time_list_var)
		#var = var / 1866240000.0
		return var

def get_min_time_var_hour (item_list , unit):
		time_list=[]
		for item in item_list:
				time_list.append(item.time)
		time_list.sort()
		if len(time_list) < 3:
				return 3240000
		ret = 3240000
		for i in range(len(time_list)-1,0 ,-1):
				for j in range(i):
						if time_list[i]-time_list[j]<=unit:
								if i-j < 3:
										ret = min(3240000, ret)
										break
								else:
										var_hour = get_var(time_list, j,i)
										ret = min(ret, var_hour)
										break
		#ret = ret / 3240000.0
		return ret


# @brief: print the user features
# @param uname: 
# @param f_list: feature vector
def print_feature(user, f_list):
	uid,uname = user[0],user[1]
	if uname.strip() == '' or uid == 0:
		return
	f_str = str(uid) + " " + uname + '\t'
	valuelist=[]
	for index, value in f_list:
		valuelist.append(str(value))
	values=','.join(valuelist)
	f_str = f_str +values + ","
	print f_str


def get_feature(item_list):
	if len(item_list) == 0:
		return

	item_list.sort(lambda d1, d2: d1.time - d2.time)
	for item in item_list:
		item.time = item.time / 1000

	valid_item_list = get_valid_item_list(item_list)

	name_ = item_list[0].uname	
	f_name_numalpha = whether_is_numalpha(name_)
	f_name_numalpha2 = whether_is_numalpha2(name_)
	f_cookie_cnt = count_cookie(valid_item_list)	
	f_ip_cnt = count_ip(valid_item_list)
	f_city_cnt = count_city(valid_item_list)
	f_forum_cnt = count_forum(valid_item_list)

	cookie_time_list = get_cookie_time_list(valid_item_list)
	f_cookie_change_freq_hour = get_change_freq(cookie_time_list, 3600) 
	f_cookie_change_freq_minute = get_change_freq(cookie_time_list, 60) 

	ip_time_list = get_ip_time_list(valid_item_list)
	f_ip_change_freq_hour = get_change_freq(ip_time_list, 3600) 
	f_ip_change_freq_minute = get_change_freq(ip_time_list, 60) 

	city_time_list = get_city_time_list(valid_item_list)
	f_city_change_freq_hour = get_change_freq(city_time_list, 3600) 
	f_city_change_freq_minute = get_change_freq(city_time_list, 60) 

	forum_time_list = get_forum_time_list(valid_item_list)
	f_forum_change_freq_hour = get_change_freq(forum_time_list, 3600)
	f_forum_change_freq_minute = get_change_freq(forum_time_list, 60)

	f_thread_add_freq_day = get_command_max_freq(item_list, sets.Set(['thread/add']), 86400)
	f_thread_add_max_freq_hour = get_command_max_freq(item_list, sets.Set(['thread/add']), 3600)
	f_thread_add_max_freq_minute = get_command_max_freq(item_list, sets.Set(['thread/add']), 60)

	f_post_add_freq_day = get_command_max_freq(item_list, sets.Set(['post/add']), 86400)
	f_post_add_max_freq_hour = get_command_max_freq(item_list, sets.Set(['post/add']), 3600)
	f_post_add_max_freq_minute = get_command_max_freq(item_list, sets.Set(['post/add']), 60)

	f_thread_add_avg_freq_hour = get_command_avg_freq(item_list, sets.Set(['thread/add']), 3600)
	f_thread_add_avg_freq_minute = get_command_avg_freq(item_list, sets.Set(['thread/add']), 60)

	f_post_add_avg_freq_hour = get_command_avg_freq(item_list, sets.Set(['post/add']), 3600)
	f_post_add_avg_freq_minute = get_command_avg_freq(item_list, sets.Set(['post/add']), 60)

	f_commit_browse_ratio = get_command_ratio(item_list, COMMIT_CMD_SET, BR_CMD_SET)
	f_fail_commit_ratio = get_fail_commit_ratio(item_list) 
	f_fail_commit_cnt = get_fail_commit_cnt(item_list) 
				

	f_quote_type_ratio = get_quote_type_ratio(item_list)
	f_quote_type_cnt = get_quote_type_cnt(item_list)
	f_commit_forum_ratio = get_commit_forum_ratio(f_thread_add_freq_day, f_post_add_freq_day, f_forum_cnt)

	f_fail_max_freq_hour = get_fail_max_freq(item_list, COMMIT_CMD_SET, 3600)
	f_fail_max_freq_minute = get_fail_max_freq(item_list, COMMIT_CMD_SET, 60)
	f_fail_avg_freq_hour = get_fail_avg_freq(item_list, COMMIT_CMD_SET, 3600)

	f_fail_post_freq = get_fail_max_freq(item_list, sets.Set(['post/add']), 86400)
	f_fail_thread_freq = get_fail_max_freq(item_list, sets.Set(['thread/add']), 86400)
	f_IP_cookie_cnt = count_IP_cookie(item_list)

	f_commit_time_var = get_time_var(item_list, COMMIT_CMD_SET)
	f_commit_min_time_var = get_min_time_var_hour(item_list, 3600)

	f = gezi.FeatureVector()

	f.add(f_name_numalpha, 'f_name_numalpha')
	f.add(f_name_numalpha2, 'f_name_numalpha2')
	
	f.add(f_cookie_cnt, 'f_cookie_cnt')
	f.add(f_ip_cnt, 'f_ip_cnt')
	f.add(f_city_cnt, 'f_city_cnt')
	f.add(f_forum_cnt, 'f_forum_cnt')
	
	f.add(f_cookie_change_freq_hour, 'f_cookie_change_freq_hour')
	f.add(f_cookie_change_freq_minute, 'f_cookie_change_freq_minute')
	f.add(f_ip_change_freq_hour, 'f_ip_change_freq_hour')
	f.add(f_ip_change_freq_minute, 'f_ip_change_freq_minute')
	f.add(f_city_change_freq_hour, 'f_city_change_freq_hour')
	f.add(f_city_change_freq_minute, 'f_city_change_freq_minute')

	f.add(f_thread_add_freq_day, 'f_thread_add_freq_day')
	f.add(f_thread_add_max_freq_hour, 'f_thread_add_max_freq_hour')
	f.add(f_thread_add_max_freq_minute, 'f_thread_add_max_freq_minute')
	
	f.add(f_post_add_freq_day, 'f_post_add_freq_day')
	f.add(f_post_add_max_freq_hour, 'f_post_add_max_freq_hour')
	f.add(f_post_add_max_freq_minute, 'f_post_add_max_freq_minute')
	
	f.add(f_thread_add_avg_freq_hour, 'f_thread_add_avg_freq_hour')
	f.add(f_post_add_avg_freq_hour, 'f_post_add_avg_freq_hour')
	
	f.add(f_commit_browse_ratio, 'f_commit_browse_ratio')

	f.add(f_fail_commit_ratio, 'f_fail_commit_ratio')
	f.add(f_fail_commit_cnt, 'f_fail_commit_cnt')

	f_hours = get_hours(item_list)
	f.add(f_hours, 'f_hours')
	f_minutes = get_minutes(item_list)
	f.add(f_minutes, 'f_minutes')

	f_night_ratio = get_night_ratio(item_list)
	f.add(f_night_ratio, 'f_night_ratio')
	f_thread_post_ratio = get_thread_post_ratio(valid_item_list)
	f.add(f_thread_post_ratio, 'f_thread_post_ratio')
	
	f_null_refer_cnt = get_post_null_refer_cnt(valid_item_list)
	f.add(f_null_refer_cnt, 'f_null_refer_cnt')

	f_pic_num = get_pic_num(valid_item_list)
	f.add(f_pic_num, 'f_pic_num')
	f_pic_ent = get_pic_ent(valid_item_list)
	f.add(f_pic_ent, 'f_pic_ent')
	
	f_video_num = get_video_num(valid_item_list)
	f.add(f_video_num, 'f_video_num')
			 
	f.add(f_quote_type_cnt, 'f_quote_type_cnt')
	f.add(f_quote_type_ratio, 'f_quote_type_ratio')
	f.add(f_commit_forum_ratio, 'f_commit_forum_ratio')

	f.add(f_fail_max_freq_hour, 'f_fail_max_freq_hour')
	f.add(f_fail_max_freq_minute, 'f_fail_max_freq_minute')
	f.add(f_fail_avg_freq_hour, 'f_fail_avg_freq_hour')

	f.add(f_fail_post_freq, 'f_fail_post_freq')
	f.add(f_fail_thread_freq, 'f_fail_thread_freq')
	f.add(f_IP_cookie_cnt, 'f_IP_cookie_cnt')

	f.add(f_commit_time_var, 'f_commit_time_var')
	f.add(f_commit_min_time_var, 'f_commit_min_time_var')
	f_post_ent = get_post_ent(valid_item_list)
	f.add(f_post_ent, 'f_post_ent')

	seq_f_list = get_seq_feature(item_list, seq_map, 2)
	#cnt = len(f_list)
	for index,value in seq_f_list:
		f.add(value, 'f_seq' + str(index))

	print '\t'.join([str(item_list[0].uid), str(f.Length()), f.str(), f.Str(), ','.join(f.names())])
#start here

seq_map = get_seq_map("./seq_feature")
		
item_list = []
last_uid = None
proce_uid=None
has_post = False 
num_errors = 0
for line in sys.stdin:
	try:
		uid, cookie, uname, time_, open_id, pro, mid, command, url, uip, refer, fid, fname, tid, nation, province, city, error_no, is_pv, email, mobile, agent, qword, video_num, image_num, quote_type = line.rstrip('\n').split('\t')
		if len(item_list) > 10000:
			#sys.stderr.write("length of item_list is too big for uid [%d]\n"%(item_list[0].uid))
			continue
			
		item = Item()
		item.uid, item.cookie, item.uname, item.time = int(uid), cookie, uname, int(time_)
		item.open_id, item.pro, item.mid, item.command = open_id, pro, mid, command
		item.url, item.uip, item.refer, item.fid, item.fname = url, int(uip), refer, int(fid), fname
		item.tid, item.nation, item.province, item.city, item.error_no = int(tid), nation, province, city, int(error_no)
		item.is_pv, item.email, item.mobile, item.agent, item.qword = int(is_pv), email, mobile, agent, qword
		item.video_num, item.image_num ,item.quote_type = int(video_num), int(image_num),int(quote_type)

		if item.error_no != 0:
			if num_errors > 100:
				continue
			num_errors += 1

		if item.command in COMMIT_CMD_SET and item.error_no == 0:
			has_post = True

		proce_uid=item.uid
		if last_uid != item.uid:
			if has_post:
				get_feature(item_list)
			item_list = []
			has_post = False
			num_errors = 0
		
		item_list.append(item)	
		last_uid = item.uid
		
	except Exception, ex:
		traceback.print_exc()
		pass
if proce_uid==last_uid:
	try:
		if has_post:
			get_feature(item_list)
	except Exception,ex:
		traceback.print_exc()
	
