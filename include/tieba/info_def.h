/**
 *  ==============================================================================
 *
 *          \file   tieba/info_def.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-02 11:09:23.064938
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_INFO_DEF_H_
#define TIEBA_INFO_DEF_H_

namespace gezi {
namespace tieba {

	struct ReplyInfo
	{
		uint64 tid;
		uint64 uid;
		uint64 pid;
		uint64 ip;
		uint64 time;
	};

	struct UserInfo
	{
		uint64 uid;
		string uname;
		uint64 regTime;
		int sex;
		int followCount;
		int followedCount;
	};

	struct ThreadInfo
	{
		uint64 tid;
		uint64 uid;
		uint64 pid;
		uint64 fid; //forum_id
		string forumName;
		uint64 time;
		uint64 ip;
		string address;
		string title;
		string content;
		bool isDeleted = false;
		bool hasMedia = false; //pic,vedio ◊¢“‚Url≤ªÀ„
	};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_DEF_H_
