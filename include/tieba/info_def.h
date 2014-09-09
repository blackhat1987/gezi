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

#include "../common_def.h"
#include "serialize_util.h"
#include "common_util.h"

namespace gezi {
	namespace tieba {

		struct PostInfo
		{
			uint64 postId = 0; 
			uint64 threadId = 0; 
			uint userId = 0; 
			uint forumId = 0; 
			uint64 ip = 0;
			uint64 createTime = 0;
			string title;
			string content;
			string userName;
			string forumName;

			bool IsThread()
			{
				return !startswith(title, "回复：");
			}

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(postId);
				ar & BOOST_SERIALIZATION_NVP(threadId);
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(forumId);
				ar & BOOST_SERIALIZATION_NVP(ip);
				ar & BOOST_SERIALIZATION_NVP(createTime);
				ar & BOOST_SERIALIZATION_NVP(title);
				ar & BOOST_SERIALIZATION_NVP(content);
				ar & BOOST_SERIALIZATION_NVP(userName);
				ar & BOOST_SERIALIZATION_NVP(forumName);
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
			uint userId = 0;
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

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(numPosts);
				ar & BOOST_SERIALIZATION_NVP(pids);
				ar & BOOST_SERIALIZATION_NVP(tids);
				ar & BOOST_SERIALIZATION_NVP(times);
				ar & BOOST_SERIALIZATION_NVP(fids);
				ar & BOOST_SERIALIZATION_NVP(fnames);
				ar & BOOST_SERIALIZATION_NVP(titles);
				ar & BOOST_SERIALIZATION_NVP(contents);
				ar & BOOST_SERIALIZATION_NVP(ips);
				ar & BOOST_SERIALIZATION_NVP(isThreads);
				ar & BOOST_SERIALIZATION_NVP(isPostsDeleted);
			}
		};

		struct FullPostsInfo
		{
			uint64 threadId = 0; //如果是0表示没有获取到信息 FullPostInfo数据无效
			uint forumId = 0;
			string title;
			string forumName;
			bool isDeleted = false;
			int numPosts = 0;
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

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(threadId);
				ar & BOOST_SERIALIZATION_NVP(forumId);
				ar & BOOST_SERIALIZATION_NVP(title);
				ar & BOOST_SERIALIZATION_NVP(forumName);
				ar & BOOST_SERIALIZATION_NVP(isDeleted);
				ar & BOOST_SERIALIZATION_NVP(numPosts);
				ar & BOOST_SERIALIZATION_NVP(pids);
				ar & BOOST_SERIALIZATION_NVP(uids);
				ar & BOOST_SERIALIZATION_NVP(ips);
				ar & BOOST_SERIALIZATION_NVP(times);
				ar & BOOST_SERIALIZATION_NVP(unames);
				ar & BOOST_SERIALIZATION_NVP(contents);
			}
		};

		struct ReplyInfo
		{
			uint64 threadId;
			uint64 userId;
			uint64 postId;
			uint forumId;
			uint64 ip;
			uint64 createTime;
		};

		struct UserInfo
		{
			uint userId = 0;
			string userName;
			uint64 regTime = 0;
			int userSex = 0; //0 没写, 1 male, 2 female
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

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(userName);
				ar & BOOST_SERIALIZATION_NVP(regTime);
				ar & BOOST_SERIALIZATION_NVP(userSex);
				ar & BOOST_SERIALIZATION_NVP(followCount);
				ar & BOOST_SERIALIZATION_NVP(followedCount);
				ar & BOOST_SERIALIZATION_NVP(email);
				ar & BOOST_SERIALIZATION_NVP(mobile);
				ar & BOOST_SERIALIZATION_NVP(birthYear);
				ar & BOOST_SERIALIZATION_NVP(isGroupOwner);
				ar & BOOST_SERIALIZATION_NVP(userType);
				ar & BOOST_SERIALIZATION_NVP(userStatus);
				ar & BOOST_SERIALIZATION_NVP(userTag);
				ar & BOOST_SERIALIZATION_NVP(userDetail);
			}
		};

		struct UserPostNumInfo
		{
			uint userId = 0;
			int numPosts = 0;
			int numThreads = 0;
			int numGoods = 0;
			int numPhotos = 0;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(numPosts);
				ar & BOOST_SERIALIZATION_NVP(numThreads);
				ar & BOOST_SERIALIZATION_NVP(numGoods);
				ar & BOOST_SERIALIZATION_NVP(numPhotos);
			}
		};

		//用户关注吧的信息 可能有用的特征
		//用户在当前吧的级别，用户关注吧数目，用户关注吧最大等级，用户关注吧等级之和,用户当前吧级别和最大等级吧等级差别
		struct UserLikeForumInfo
		{
			struct Node
			{
				string forumName;
				uint64 time;
				int level;
				int curScore;
				int leftScore;

				friend class boost::serialization::access;
				template<class Archive>
				void serialize(Archive &ar, const unsigned int version)
				{
					ar & BOOST_SERIALIZATION_NVP(forumName);
					ar & BOOST_SERIALIZATION_NVP(time);
					ar & BOOST_SERIALIZATION_NVP(level);
					ar & BOOST_SERIALIZATION_NVP(curScore);
					ar & BOOST_SERIALIZATION_NVP(leftScore);
				}
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

			uint userId = 0;
			int maxLevel = 0;
			int numLikes = 0;
			int sumLevels = 0;
			map<uint, Node> infoMap;
			vector<string> forumNames;
			vector<int> levels;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(maxLevel);
				ar & BOOST_SERIALIZATION_NVP(numLikes);
				ar & BOOST_SERIALIZATION_NVP(sumLevels);
				ar & BOOST_SERIALIZATION_NVP(infoMap);
				ar & BOOST_SERIALIZATION_NVP(forumNames);
				ar & BOOST_SERIALIZATION_NVP(levels);
			}
		};

		struct ThreadInfo
		{
			uint64 threadId = 0;
			uint64 userId;
			uint64 postId;
			uint forumId; //forum_id
			string forumName;
			uint64 createTime;
			uint64 ip;
			string address;
			string title;
			string content;
			bool isDeleted = false;
			bool hasMedia = false; //pic,vedio 注意Url不算

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(threadId);
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(postId);
				ar & BOOST_SERIALIZATION_NVP(forumId);
				ar & BOOST_SERIALIZATION_NVP(forumName);
				ar & BOOST_SERIALIZATION_NVP(createTime);
				ar & BOOST_SERIALIZATION_NVP(ip);
				ar & BOOST_SERIALIZATION_NVP(address);
				ar & BOOST_SERIALIZATION_NVP(title);
				ar & BOOST_SERIALIZATION_NVP(content);
				ar & BOOST_SERIALIZATION_NVP(isDeleted);
				ar & BOOST_SERIALIZATION_NVP(hasMedia);
			}
		};

		struct DeleteInfo
		{
			uint64 tid = 0;
			uint64 pid = 0;
			string opUid;
			string monitorType; //17007等 吧务删除是0
			uint64 opTime = 0;
			bool isDeleted = false;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(tid);
				ar & BOOST_SERIALIZATION_NVP(pid);
				ar & BOOST_SERIALIZATION_NVP(opUid);
				ar & BOOST_SERIALIZATION_NVP(monitorType);
				ar & BOOST_SERIALIZATION_NVP(opTime);
				ar & BOOST_SERIALIZATION_NVP(isDeleted);
			}
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

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(fid);
				ar & BOOST_SERIALIZATION_NVP(rank);
				ar & BOOST_SERIALIZATION_NVP(hotValue);
				ar & BOOST_SERIALIZATION_NVP(level1Name);
				ar & BOOST_SERIALIZATION_NVP(level2Name);
			}
		};

		struct UrlInfo
		{
			string url; //url不为空标记有效
			float rank = 0.0;
			bool isJump = false;
			float jumRank = 0.0;
			string content;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(url);
				ar & BOOST_SERIALIZATION_NVP(rank);
				ar & BOOST_SERIALIZATION_NVP(isJump);
				ar & BOOST_SERIALIZATION_NVP(jumRank);
				ar & BOOST_SERIALIZATION_NVP(content);
			}
		};

		static const int kMaxRequestCount = 100;
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_DEF_H_
