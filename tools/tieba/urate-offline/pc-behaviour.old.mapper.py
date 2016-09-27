#!/usr/bin/env python

import sys
import urllib
import traceback
import sets

CMD_SET=sets.Set(['f/frs', 'add', 'thread/add', 'post/add', '20-0','panel', 'browse/comment/list','browse/picture/guide','browse/picture/toplist', 'replyme','jump','main', 'atme', 'get_forumlist', 'upload/pic', 'others', 'cm_click_pic','f/good', 'browse/photo/AlbumRecommend', 'post/delete', 'thread/delete', 'recycle', 'my_tie', 'forum', 'view_album', 'allfeed', 'fans', 'storethread', 'browse/photo/frsInfo', 'like/commit/notice/delete', 'like/commit/add', 'comment/comment'])
BR_CMD_SET=sets.Set(['f/frs', '20-0', 'browse/comment/list', 'browse/picture/guide', 'browse/picture/toplist','replyme','jump','main', 'atme', 'get_forumlist','f/good', 'browse/photo/AlbumRecommend','recycle', 'my_tie', 'forum', 'view_album', 'allfeed', 'fans','browse/photo/frsInfo'])
COMMIT_CMD_SET=sets.Set(['thread/add', 'post/add'])
UI_CMD_SET = sets.Set(['like/commit/notice/delete', 'like/commit/add', 'comment/comment'])

CMD_SET = CMD_SET.union(BR_CMD_SET).union(COMMIT_CMD_SET).union(UI_CMD_SET)


class Item:
	pass

def get_int(s, value):
	if not s.isdigit():
		return value
	return int(s)


for line in sys.stdin:
	try:
		line = urllib.unquote(line.strip('\n'))
		s = line.split("\t")
		if len(s) < 40:
                        continue
		if s[0].isdigit():
			s.insert(0, '')
		item = Item()
		item.cookie = s[0]
		item.uid = int(s[1])
		item.uname = s[2]
		item.time = get_int((s[4]),0)
		item.open_id = s[5]
		item.pro = s[6]
		item.mid = s[7]
		item.command = s[8]

		if item.uid == 0:
			continue
		if item.open_id == 'wap' or item.open_id == 'tbclient':
			continue
		if item.pro == 'app' or item.pro == 'client' or item.pro == 'wap':
			continue
		if not item.command in COMMIT_CMD_SET:
			continue

		item.url = s[9]
		item.uip = get_int(s[10], 0)
		item.refer = s[11]
		item.fid = s[12]
		item.fid = get_int(item.fid, 0)

		item.fname = s[13]
		item.tid = s[14]
		item.tid = get_int(s[14], 0)

		item.nation = s[21]
		item.province = s[22]
		item.city = s[23]
		item.error_no = get_int(s[24], 0)
		item.is_pv = get_int(s[25], 0)

		item.email = s[28]
		item.mobile = s[29]
		item.agent = s[30]
		item.qword = s[32]
		item.video_num = get_int(s[36], 0)
		item.image_num = get_int(s[37], 0)
                item.quotetype = get_int(s[40], 0)
                
                first_dir=s[47]
                if first_dir.find("\xc3\xf7\xd0\xc7") != -1:
                   continue
                if item.uname.find("\xcd\xe2\xbd\xbb")!=-1:
					continue

		out_str = "%d\t%s\t%s\t%d\t%s\t%s\t%s\t%s"%(item.uid, item.cookie, item.uname, item.time, item.open_id, item.pro, item.mid, item.command)
		out_str = out_str + "\t" + ("%s\t%d\t%s\t%d\t%s"%(item.url, item.uip, item.refer, item.fid, item.fname))
		out_str = out_str + "\t" + ("%d\t%s\t%s\t%s\t%d"%(item.tid, item.nation, item.province, item.city, item.error_no))	  	
		out_str = out_str + "\t" + ("%d\t%s\t%s\t%s\t%s"%(item.is_pv, item.email, item.mobile, item.agent, item.qword))
		out_str = out_str + "\t" + ("%d\t%d\t%d"%(item.video_num, item.image_num,item.quotetype))

		print out_str

	except Exception,ex:
		sys.stderr.write("error line:%s\n"%line)
		traceback.print_exc()
		continue


