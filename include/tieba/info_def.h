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

	struct PostInfo
	{
		uint64 pid = 0; //@TODO 基础代码不再使用缩写
		uint64 tid;
		uint64 uid;
		uint64 fid; //forumId
		uint64 ip;
		uint64 time;
		string title;
		string content;
		string uname;
		string forumName;

		bool IsValid()
		{
			return pid != 0;
		}

		bool IsThread()
		{
			return !startswith(title, "回复：");
		}
	};

	struct FullPostsInfo
	{
		struct Post
		{
			uint64 pid;
			uint64 uid;
			uint64 ip;
			uint64 time;
			string uname;
			string content;
		};
		uint64 tid = 0; //如果是0表示没有获取到信息 FullPostInfo数据无效
		uint64 fid = 0;
		string title;
		string forumName;
		bool isDeleted = false;
		int numTotalPosts = 0;
		vector<Post> posts;

		bool IsValid()
		{
			return tid != 0;
		}
	};

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
		uint64 tid = 0;
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
		bool hasMedia = false; //pic,vedio 注意Url不算
	};

	struct DeleteInfo
	{
		uint64 tid = 0;
		uint64 pid = 0;
		string opUid;
		string monitorType; //17007等 吧务删除是0
		uint64 opTime = 0;
		bool isDeleted = false;
	};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_DEF_H_
