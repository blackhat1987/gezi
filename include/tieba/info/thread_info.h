/**
 *  ==============================================================================
 *
 *          \file   tieba/info/thread_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-05 11:34:02.413246
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_INFO_THREAD_INFO_H_
#define TIEBA_INFO_THREAD_INFO_H_

#include "tieba/get_info.h"
#include "tieba/info_def.h"

namespace gezi {
	namespace tieba {
		//--------------------------------------thread信息
		//批量获取主题信息 事实上只提供vector<uint64>的输入接口即可 get_info里面的接口也是 不过这个配合test_cached_fetcher.cc测试了下在重载函数的情况下 如何bind
		//另外的之前有个问题是注意返回的结果顺序和输入的id顺序不一致 因为结果是map 虽然接口展示页面显示顺序是和输入一致 但是json内部使用类似std::map就变成按照id大小排序了
		//失败的不加入数组！
		inline vector<ThreadInfo> get_threads_info(const svec& tidVec, bool need_abstract = true, bool allowError = true)
		{
			vector<ThreadInfo> resultVec;
			vector<svec> tidsVec = gezi::split(tidVec, kMaxRequestCount * 0.5);
			for (auto& tids : tidsVec)
			{
				string jsonResult = tieba::get_threads_info_str(tids, need_abstract);
				PVAL(jsonResult);

				Json::Reader reader;
				Json::Value root;
				bool ret = reader.parse(jsonResult, root);
				if (!ret)
				{
					LOG(WARNING) << "json parse fail: " << jsonResult;
					if (!allowError)
					{
						resultVec.clear();
						return resultVec;
					}
					continue;
				}
				try
				{
					auto& m = root["output"]["thread_list"];
					//http://stackoverflow.com/questions/9984907/looping-through-all-items-of-the-json-with-text-index-on-jsoncpp
					//这里调整成为按照输入顺序排序 更好的方法？@TODO jsoncpp的map遍历不能保证输入的原有顺序了另外遍历不够友好为什么不能返回一个iter 直接 (*iter)["title"].asString()参考stackoverflow和源代码
					const auto& memberNames = m.getMemberNames();
					typedef decltype(memberNames.begin()) Iter;
					map<string, Iter> tid2IterMap;
					for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
					{
						tid2IterMap[*iter] = iter;
					}
					for (auto tid : tids)
					{
						auto it = tid2IterMap.find(tid);
						if (it == tid2IterMap.end())
						{
							continue;
						}
						auto iter = it->second; //存在tid不在map中的可能
						auto& jsonInfo = m[*iter];
						ThreadInfo node;
						node.title = jsonInfo["title"].asString();
						node.userId = jsonInfo["user_id"].asUInt64();
						node.ip = jsonInfo["user_ip"].asUInt64();
						node.forumId = jsonInfo["forum_id"].asUInt64();
						node.postId = jsonInfo["first_post_id"].asUInt64();
						node.isDeleted = jsonInfo["is_deleted"].asBool();
						node.createTime = jsonInfo["last_modified_time"].asInt64();
						node.forumName = jsonInfo["forum_name"].asString();
						if (need_abstract)
						{
							node.content = jsonInfo["abstract"].asString();
							node.hasMedia = !jsonInfo["media"].empty();
						}
						node.threadId = UINT64(*iter);
						resultVec.emplace_back(node);
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << jsonResult;
					if (!allowError)
					{
						resultVec.clear();
						return resultVec;
					}
				}
			}
			return resultVec;
		}

		inline vector<ThreadInfo> get_threads_info(const vector<uint64>& tidVec, bool need_abstract = true, bool allowError = true)
		{
			return get_threads_info(convert(tidVec), need_abstract, allowError);
		}

		inline map<uint64, ThreadInfo> get_threads_info_map(const vector<uint64>& tidVec, bool need_abstract = true)
		{
			map<uint64, ThreadInfo> threadsInfoMap;
			auto tidsVec = gezi::split(tidVec, kMaxRequestCount * 0.5);
			for (auto& tids : tidsVec)
			{
				string jsonResult = tieba::get_threads_info_str(convert(tids), need_abstract);
				PVAL(jsonResult);

				Json::Reader reader;
				Json::Value root;
				bool ret = reader.parse(jsonResult, root);
				if (!ret)
				{
					LOG(WARNING) << "json parse fail: " << jsonResult;
					continue;
				}
				try
				{
					auto& m = root["output"]["thread_list"];
					//http://stackoverflow.com/questions/9984907/looping-through-all-items-of-the-json-with-text-index-on-jsoncpp
					//这里调整成为按照输入顺序排序 更好的方法？@TODO jsoncpp的map遍历不能保证输入的原有顺序了另外遍历不够友好为什么不能返回一个iter 直接 (*iter)["title"].asString()参考stackoverflow和源代码
					const auto& memberNames = m.getMemberNames();
					for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
					{
						auto& jsonInfo = m[*iter];
						ThreadInfo node;
						node.title = jsonInfo["title"].asString();
						node.content = jsonInfo["content"].asString();
						node.userId = jsonInfo["user_id"].asUInt64();
						node.ip = jsonInfo["user_ip"].asUInt64();
						node.forumId = jsonInfo["forum_id"].asUInt64();
						node.postId = jsonInfo["first_post_id"].asUInt64();
						node.isDeleted = jsonInfo["is_deleted"].asBool();
						node.createTime = jsonInfo["last_modified_time"].asInt64();
						node.forumName = jsonInfo["forum_name"].asString();
						if (need_abstract)
						{
							node.content = jsonInfo["abstract"].asString();
							node.hasMedia = !jsonInfo["media"].empty();
						}
						node.threadId = UINT64(*iter);
						threadsInfoMap[node.threadId] = node;
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << jsonResult;
				}
			}
			return threadsInfoMap;
		}

		inline ThreadInfo get_thread_info(uint64 threadId, bool need_abstract = true, bool allowError = true)
		{
			vector<uint64> vec = { threadId };
			vector<ThreadInfo> results = get_threads_info(vec, need_abstract, allowError);
			ThreadInfo threadInfo;
			if (!results.empty())
			{
				threadInfo = results[0];
			}
			return threadInfo;
		}
		//-------------------------------------楼信息
		inline FullPostsInfo get_full_posts_info(uint64 threadId, int resNum = 100, int offset = 0, int hasComment = 0, uint64 postId = 0)
		{ 
			FullPostsInfo info;
			string jsonResult = tieba::get_full_posts_info_str(threadId, resNum, offset, hasComment, postId);
			PVAL(jsonResult);

			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonResult, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail with threadId: [" << threadId << "] " << jsonResult;
				return info;
			}
			try
			{
				auto& m = root["output"]["output"][0];
				info.isDeleted = m["is_thread_deleted"].asBool();
				info.numPosts = m["total_post_num"].asInt();
				{
					int i = 0;
					for (auto& post : m["post_infos"])
					{
						if (i == 0)
						{
							info.forumId = post["forum_id"].asUInt();
							info.forumName = post["word"].asString();
							info.title = post["title"].asString();
						}
						info.contents.push_back(post["content"].asString());
						info.uids.push_back(post["user_id"].asUInt());
						info.unames.push_back(post["username"].asString());
						info.ips.push_back(post["ip"].asUInt64());
						info.pids.push_back(post["post_id"].asUInt64());
						info.times.push_back(post["now_time"].asInt64());
						info.commentsVec.push_back(vector<CommentInfo>());
						if (post.isMember("comment_info"))   
						{
							for (auto& jsonComment : post["comment_info"])
							{
								CommentInfo commentInfo;
								commentInfo.threadId = UINT64(jsonComment["thread_id"].asString());
								commentInfo.postId = UINT64(jsonComment["post_id"].asString());
								commentInfo.commentId = UINT64(jsonComment["comment_id"].asString());
								commentInfo.userName = jsonComment["username"].asString();
								commentInfo.userId = UINT(jsonComment["user_id"].asString());
								commentInfo.ip = jsonComment["ip"].asUInt64();
								commentInfo.createTime = jsonComment["now_time"].asInt64();
								commentInfo.content = jsonComment["content"].asString();
								info.commentsVec.back().emplace_back(commentInfo);
							}
						}
						i++;
					}
				}
				info.threadId = threadId; //标记数据读取成功了
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
			}
			return info;
		}
	} //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_THREAD_INFO_H_
