/**
 *  ==============================================================================
 *
 *          \file   tieba/info/user_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-05 11:34:16.933450
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_INFO_USER_INFO_H_
#define TIEBA_INFO_USER_INFO_H_

#include "tieba/get_info.h"
#include "tieba/info_def.h"

namespace gezi {
	namespace tieba {

		inline void parse_user_post_num_info_(const Json::Value& root, UserPostNumInfo& info)
		{
			auto& m = root["count"];
			info.numPosts = m["post_num"].asInt();
			info.numThreads = m["thread_num"].asInt();
			try
			{ //@TODO 贴吧bug
				info.numGoods = m["good_num"].asInt();
			}
			catch (...)
			{
				LOG(WARNING) << "Tieba error will set good num to 0";
				info.numGoods = 0;
			}
			info.numPhotos = m["photo_num"].asInt();
			info.userId = m["user_id"].asUInt();
		}

		inline UserPostNumInfo get_user_post_num_info_(string url)
		{
			UserPostNumInfo info;
			string jsonStr = get_info_str(url, 5000);
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail: " << jsonStr << " url: " << url;
				return info;
			}
			try
			{
				parse_user_post_num_info_(root, info);
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail: " << jsonStr << " url: " << url;
			}
			return info;
		}

		inline UserPostNumInfo get_user_post_num_info(uint uid)
		{
			string url = "http://service.tieba.baidu.com/service/post?method=queryUserCount&format=json&user_id=" + STR(uid);
			return get_user_post_num_info_(url);
		}

		inline UserPostNumInfo get_user_post_num_info(uint uid, uint forumId)
		{
			string url = (boost::format("http://service.tieba.baidu.com/service/post?method=queryUserForumCount&format=json&user_id=%1%&forum_id=%2%") % uid % forumId).str();
			return get_user_post_num_info_(url);
		}

		inline UserLikeForumInfo get_user_like_forum_info(uint uid)
		{
			UserLikeForumInfo info;
			string url = "http://service.tieba.baidu.com/service/perm?method=getLikeForumListIndex&format=json&check_forum=1&user_id=" + STR(uid);
			PVAL(url);
			string jsonStr = get_info_str(url);
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail uid:[" << uid << "]";
				return info;
			}
			try
			{
				auto& m = root["output"]["member_list"];
				const auto& memberNames = m.getMemberNames();
				info.numLikes = memberNames.size();
				for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
				{
					auto& jsonInfo = m[*iter];
					UserLikeForumInfo::Node node;
					node.forumName = jsonInfo["forum_name"].asString();
					node.level = jsonInfo["level_id"].asInt();
					node.time = jsonInfo["in_time"].asInt64();
					node.curScore = jsonInfo["cur_score"].asInt();
					node.leftScore = jsonInfo["score_left"].asInt();
					if (node.level > info.maxLevel)
					{
						info.maxLevel = node.level;
					}
					info.sumLevels += node.level;
					//info.infoMap[UINT(*iter)] = node;
					info.infoMap[node.forumName] = node;
					info.forumNames.push_back(node.forumName);
					info.levels.push_back(node.level);
				}
				info.userId = uid;
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail: " << jsonStr << " url: " << url;
			}
			return info;
		}

		inline void parse_user_info_(const Json::Value& m, UserInfo& info, bool needFollowInfo, bool needPassInfo)
		{
			info.userName = m["user_name"].asString();
			info.userSex = m["user_sex"].asInt();
			info.userType = m["user_type"].asInt();
			info.userStatus = m["user_status"].asInt();
			info.isGroupOwner = INT(m["is_group_owner"].asString());
			if (needFollowInfo)
			{
				info.followCount = m["follow_count"].asInt();
				info.followedCount = m["followed_count"].asInt();
			}
			if (needPassInfo)
			{
				auto& puserInfo = m["puserinfo"];
				info.birthYear = puserInfo["birthday_year"].asInt();
				info.regTime = puserInfo["regtime"].asInt64();
				info.mobile = puserInfo["securemobil"].asString();
				info.email = puserInfo["securemail"].asString();
				info.userDetail = puserInfo["userdetail"].asString();
				info.userTag = puserInfo["taginfo"].asString();
			}
			info.userId = m["user_id"].asUInt();
		}

		inline UserInfo get_user_info(uint uid, bool needFollowInfo = true, bool needPassInfo = true)
		{
			UserInfo info;
			string url = (boost::format("http://service.tieba.baidu.com/service/user?method=getUserDataEx&format=json&user_id=%1%&need_follow_info=%2%&need_pass_info=%3%") % uid % needFollowInfo % needPassInfo).str();
			string jsonStr = get_info_str(url);
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail: " << jsonStr << " url: " << url;
				return info;
			}
			try
			{
				auto& m = root["user_info"];
				parse_user_info_(m, info, needFollowInfo, needPassInfo);
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail: " << jsonStr << " url: " << url;
			}
			return info;
		}

		inline vector<UserInfo> get_users_info(const vector<uint> uids_, 
			bool needFollowInfo = true, bool needPassInfo = true)
		{
			vector<UserInfo> infos;
			auto uidsVec = gezi::split(uids_, kMaxRequestCount);
			for (auto& uids : uidsVec)
			{
				string url = (boost::format("http://service.tieba.baidu.com/service/user?method=mgetUserDataEx&format=json&user_id=[%1%]&need_follow_info=%2%&need_pass_info=%3%") % join(convert(uids), ",") % needFollowInfo % needPassInfo).str();
				string jsonStr = get_info_str(url);
				Json::Reader reader;
				Json::Value root;
				bool ret = reader.parse(jsonStr, root);
				if (!ret)
				{
					LOG(WARNING) << "json parse fail: " << jsonStr;
					continue;
				}
				try
				{
					auto& m = root["user_info"];
					const auto& memberNames = m.getMemberNames();
					typedef decltype(memberNames.begin()) Iter;
					map<string, Iter> id2IterMap;
					for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
					{
						id2IterMap[*iter] = iter;
					}
					for (auto id : uids)
					{
						auto it = id2IterMap.find(STR(id));
						if (it == id2IterMap.end())
						{ //如果找不到也可以放一个伪装的结果？@TODO 实际应用看需要 现在的做法是错位 如果有错误 返回数组容量比输入小
							continue;
						}
						auto iter = it->second; //存在tid不在map中的可能
						auto& jsonInfo = m[*iter];
						UserInfo info;
						parse_user_info_(jsonInfo, info, needFollowInfo, needPassInfo);
						infos.emplace_back(info);
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << jsonStr << " url: " << url;
				}
			}
			return infos;
		}

		inline map<uint, UserInfo> get_users_info_map(const vector<uint> uids_, bool needFollowInfo = true, bool needPassInfo = true)
		{
			map<uint, UserInfo> infos;
			auto uidsVec = gezi::split(uids_, kMaxRequestCount);
			for (auto& uids : uidsVec)
			{
				string url = (boost::format("http://service.tieba.baidu.com/service/user?method=mgetUserDataEx&format=json&user_id=[%1%]&need_follow_info=%2%&need_pass_info=%3%") % join(convert(uids), ",") % needFollowInfo % needPassInfo).str();
				string jsonStr = get_info_str(url);
				Json::Reader reader;
				Json::Value root;
				bool ret = reader.parse(jsonStr, root);
				if (!ret)
				{
					LOG(WARNING) << "json parse fail: " << jsonStr;
					continue;
				}
				try
				{
					auto& m = root["user_info"];
					const auto& memberNames = m.getMemberNames();
					for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
					{
						auto& jsonInfo = m[*iter];
						UserInfo info;
						parse_user_info_(jsonInfo, info, needFollowInfo, needPassInfo);
						infos[info.userId] = info;
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << jsonStr << " url: " << url;
				}
			}
			return infos;
		}

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_USER_INFO_H_
