/**
 *  ==============================================================================
 *
 *          \file   tieba/info/user_posts_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-07 14:31:07.422448
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_INFO_USER_POSTS_INFO_H_
#define TIEBA_INFO_USER_POSTS_INFO_H_
#include "tieba/get_info.h"
#include "tieba/info_def.h"
#include "tieba/info/forum_info.h"
namespace gezi {
namespace tieba {
	//用户的最近发帖信息
	inline UserPostsInfo get_user_posts_info(uint uid, int resNum = 25, bool needContent = true, uint64 endTime = 0, int orderType = 1, int offset = 0)
	{
		UserPostsInfo info;
		string url = !endTime ?
			(boost::format("http://service.tieba.baidu.com/service/post?method=queryUserPost&format=json&input={\"user_id\":%1%,\"res_num\":%2%,\"need_content\":%3%,\"order_type\":%4%,\"offset\":%5%,\"delete_type\":2}") % uid % resNum % needContent % orderType % offset).str() :
			(boost::format("http://service.tieba.baidu.com/service/post?method=queryUserPost&format=json&input={\"user_id\":%1%,\"res_num\":%2%,\"need_content\":%3%,\"order_type\":%4%,\"offset\":%5%,\"delete_type\":2,\"end_time\":%6%}") % uid % resNum % needContent % orderType % offset % endTime).str();
		string jsonStr = get_info_str(url, 5000);
		Json::Reader reader;
		Json::Value root;
		bool ret = reader.parse(jsonStr, root);
		if (!ret)
		{
			LOG(WARNING) << "json parse fail";
			return info;
		}
		try
		{
			auto& m = root["post"]["post"];
			for (auto& jsonInfo : m)
			{
				info.pids.push_back(UINT64(jsonInfo["post_id"].asString()));
				info.tids.push_back(UINT64(jsonInfo["thread_id"].asString()));
				info.fids.push_back(UINT(jsonInfo["forum_id"].asString()));
				info.fnames.push_back(jsonInfo["forum_name"].asString());
				info.ips.push_back(UINT64(jsonInfo["ip"].asString()));
				info.times.push_back(INT64(jsonInfo["create_time"].asString()));
				info.isThreads.push_back(BOOL(jsonInfo["is_thread"].asString()));
				info.titles.push_back(jsonInfo["title"].asString());
				info.contents.push_back(jsonInfo["content"].asString());
				info.isPostsDeleted.push_back(false); //如果需要通过删帖接口获取
				info.level1Names.push_back("");
				info.level2Names.push_back("");
				info.ranks.push_back(0);
				info.hotValues.push_back(0);
			}
			info.numPosts = m.size(); //前面出现任何差错都不允许 
			if (info.numPosts > 0)
			{
				info.userId = uid;
			}
			{//获取level1,level2信息 允许出错 出错为空
				auto levelMap = get_forums_info_map(info.fids);
				for (size_t i = 0; i < info.numPosts; i++)
				{
					auto iter = levelMap.find(info.fids[i]);
					if (iter != levelMap.end())
					{
						info.level1Names[i] = (iter->second).level1Name;
						info.level2Names[i] = (iter->second).level2Name;
						info.ranks[i] = (iter->second).rank;
						info.hotValues[i] = (iter->second).hotValue;
					}
				}
			}
		}
		catch (...)
		{
			LOG(WARNING) << "get json value fail " << jsonStr << " url: " << url;
		}
		return info;
	}

	//用户的直到这个postId为止的发帖信息
	inline UserPostsInfo get_user_posts_info_until(const PostInfo& info, int resNum = 25, bool needContent = true, int orderType = 1, int offset = 0)
	{
		uint uid = info.userId;
		int64 endTime = info.createTime;
		PVAL3(uid, endTime, to_time_str(endTime));
		return get_user_posts_info(uid, resNum, needContent, endTime, orderType, offset);
	}

	inline UserPostsInfo get_user_posts_info_until(uint64 pid, int resNum = 25, bool needContent = true, int orderType = 1, int offset = 0)
	{
		PostInfo info = get_post_info(pid);
		return get_user_posts_info_until(info, resNum, needContent, orderType, offset);
	}
}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_USER_POSTS_INFO_H_
