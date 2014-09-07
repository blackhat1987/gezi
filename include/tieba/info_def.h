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
			uint fid; //forumId
			uint64 ip;
			uint64 time;
			string title;
			string content;
			string uname;
			string forumName;

			bool IsThread()
			{
				return !startswith(title, "回复：");
			}
		};

		//泛化的帖子序列信息 
		struct PostsInfo
		{
			vector<uint64> pids;
			vector<uint64> tids; //如果是楼模型这个是空 或者1 
			vector<uint> uids; //如果是用行为模型 这个是空或者1
			vector<uint64> times; //@TODO uint
			vector<uint> fids; 
			vector<string> fnames;
			vector<string> titles;
			vector<string> contents;
			vector<uint64> ips; //@TODO uint
			vector<bool> isThreads;
			size_t size()
			{
				return pids.size();
			}
		};

		struct UserPostsInfo
		{
			uint uid = 0;
			int numPosts = 0;
			vector<uint64> pids;
			vector<uint64> tids;
			vector<uint64> times;
			vector<uint> fids;
			vector<string> fnames;
			vector<string> titles;
			vector<string> contents;
			vector<uint64> ips;
			vector<bool> isThreads;
			vector<bool> isPostsDeleted;
			size_t size()
			{
				return pids.size();
			}
		};

		struct FullPostsInfo
		{
			uint64 tid = 0; //如果是0表示没有获取到信息 FullPostInfo数据无效
			uint fid = 0;
			string title;
			string forumName;
			bool isDeleted = false;
			int numTotalPosts = 0;
			vector<uint64> pids;
			vector<uint> uids;
			vector<uint64> ips;
			vector<uint64> times;
			vector<string> unames;
			vector<string> contents;

			size_t size()
			{
				return pids.size();
			}
		};

		struct ReplyInfo
		{
			uint64 tid;
			uint64 uid;
			uint64 pid;
			uint fid;
			uint64 ip;
			uint64 time;
		};

		struct UserInfo
		{
			uint uid = 0;
			string uname;
			uint64 regTime = 0;
			int sex = 0; //0 没写, 1 male, 2 female
			int followCount = 0; //关注数
			int followedCount = 0; //粉丝数
			string email;
			string mobile;
			int birthYear = 0;
			int isGroupOwner = 0; //0,1,2
			int userType = 0; //0, 1 vip
			int userStatus = 0; //0, 1不允许被关注
			string userTag;
			string userDetail;
		};

		struct UserPostNumInfo
		{
			uint uid = 0;
			int numPosts;
			int numThreads;
			int numGoods;
			int numPhotos;
		};

		//用户关注吧的信息 可能有用的特征
		//用户在当前吧的级别，用户关注吧数目，用户关注吧最大等级，用户关注吧等级之和,用户当前吧级别和最大等级吧等级差别
		struct UserLikeForumInfo
		{
			struct Node
			{
				string fname;
				uint64 time;
				int level;
				int curScore;
				int leftScore;
			};

			//获取在当前吧下的等级
			int GetLevel(uint forumId)
			{
				auto iter = infoMap.find(forumId);
				if (iter != infoMap.end())
				{
					return (iter->second).level;
				}
				return 0;
			}

			uint uid;
			int maxLevel = 0;
			int numLikes = 0;
			int sumLevels = 0;
			map<uint, Node> infoMap;
			vector<string> fnames;
			vector<int> levels;
		};

		struct ThreadInfo
		{
			uint64 tid = 0;
			uint64 uid;
			uint64 pid;
			uint fid; //forum_id
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

		//forum_dir      output{            //输出数据
		//	uint32_t  rank                //二级目录吧按热度排名 （目前不更新）
		//	string    level_1_name        //一级目录
		//	string    level_2_name        //二级目录
		//	uint32_t  hot_value           //热度值 （目前不更新）
		struct ForumInfo
		{
			uint fid = 0;
			uint rank;
			uint hotValue;
			string level1Name;
			string level2Name;
		};

		struct UrlInfo
		{
			string url; //url不为空标记有效
			float rank = 0.0;
			bool isJump = false;
			float jumRank = 0.0;
			string content;
		};

		const int kMaxRequestCount = 100;
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_DEF_H_
