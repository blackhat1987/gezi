/**
 *  ==============================================================================
 *
 *          \file   tieba/get_parsed_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-02 11:18:37.296284
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_GET_PARSED_INFO_H_
#define TIEBA_GET_PARSED_INFO_H_

#include "tieba/get_info.h"
#include "tieba/info_def.h"

namespace gezi {
	namespace tieba {
		//--------------------------------------post信息
		//获取帖子标题内容
		inline bool get_post_info(uint64 pid, string& title, string& content)
		{
			string jsonStr = get_post_info_str(pid);

			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return false;
			}

			try
			{
				auto& m = root["output"][0];
				title = m["title"].asString();
				content = m["content"].asString();
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
				return false;
			}
			return true;
		}

		inline void parse_post_info(const Json::Value& m, PostInfo& info)
		{
			info.title = m["title"].asString();
			info.content = m["content"].asString();
			info.fid = m["forum_id"].asUInt64();
			info.forumName = m["word"].asString();
			info.ip = m["ip"].asUInt64();
			//info.tid = m["thread_id"].asUInt64(); //Type is not convertible to UInt64 @TODO 按说应该支持直接转吧。。
			info.tid = UINT64(m["thread_id"].asString());
			info.uname = m["username"].asString();
			info.time = m["now_time"].asUInt64();
		}

		inline PostInfo get_post_info(uint64 pid)
		{
			PostInfo info;
			string jsonStr = get_post_info_str(pid);

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
				const auto& m = root["output"][0];
				parse_post_info(m, info);
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
				return info;
			}
			info.pid = pid;
			return info;
		}

		inline vector<PostInfo> get_posts_info(const vector<uint64>& pids)
		{
			vector<PostInfo> resultVec;
			string jsonStr = get_posts_info_str(pids);

			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return resultVec;
			}
			try
			{
				int i = 0;
				for (const auto& m : root["output"])
				{
					PostInfo info;
					parse_post_info(m, info);
					info.pid = pids[i++];
					resultVec.emplace_back(info);
				}
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
				return resultVec;
			}

			return resultVec;
		}

		//--------------------------------------thread信息
		//批量获取主题信息 事实上只提供vector<uint64>的输入接口即可 get_info里面的接口也是 不过这个配合test_cached_fetcher.cc测试了下在重载函数的情况下 如何bind
		//另外的之前有个问题是注意返回的结果顺序和输入的id顺序不一致 因为结果是map 虽然接口展示页面显示顺序是和输入一致 但是json内部使用类似std::map就变成按照id大小排序了
		inline vector<ThreadInfo> get_threads_info(const svec& tidVec, bool need_abstract = false, bool allowError = true)
		{
			vector<ThreadInfo> resultVec;
			vector<svec> tidsVec = gezi::split(tidVec, 50);
			for (auto& tids_ : tidsVec)
			{
				string jsonResult = tieba::get_threads_info_str(tids_, need_abstract);
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
					for (auto tid : tids_)
					{
						auto iter = tid2IterMap[tid];
						auto& jsonInfo = m[*iter];
						ThreadInfo node;
						node.title = jsonInfo["title"].asString();
						node.uid = jsonInfo["user_id"].asUInt64();
						node.ip = jsonInfo["user_ip"].asUInt64();
						node.fid = jsonInfo["forum_id"].asUInt64();
						node.pid = jsonInfo["first_post_id"].asUInt64();
						node.isDeleted = jsonInfo["is_deleted"].asBool();
						node.time = jsonInfo["last_modified_time"].asUInt64();
						node.forumName = jsonInfo["forum_name"].asString();
						if (need_abstract)
						{
							node.content = jsonInfo["abstract"].asString();
							node.hasMedia = !jsonInfo["media"].empty();
						}
						node.tid = UINT64(*iter);
						resultVec.emplace_back(node);
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail";
					if (!allowError)
					{
						resultVec.clear();
						return resultVec;
					}
				}
			}
			return resultVec;
		}

		inline vector<ThreadInfo> get_threads_info(const vector<uint64>& tidVec, bool need_abstract = false, bool allowError = true)
		{
			return get_threads_info(convert(tidVec), need_abstract, allowError);
		}

		inline ThreadInfo get_thread_info(uint64 threadId, bool need_abstract = false, bool allowError = true)
		{
			vector<uint64> vec = { threadId };
			vector<ThreadInfo> results = get_threads_info(vec);
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
				LOG(WARNING) << "json parse fail: " << jsonResult;
				return info;
			}
			try
			{
				auto& m = root["output"]["output"][0];
				info.isDeleted = m["is_thread_deleted"].asBool();
				info.numTotalPosts = m["total_post_num"].asInt();
				{
					int i = 0;
					for (auto& post : m["post_infos"])
					{
						FullPostsInfo::Post postInfo;
						if (i == 0)
						{
							info.fid = post["forum_id"].asUInt64();
							info.forumName = post["word"].asString();
							info.title = post["title"].asString();
						}
						postInfo.content = post["content"].asString();
						postInfo.uid = post["user_id"].asUInt64();
						postInfo.uname = post["username"].asString();
						postInfo.ip = post["ip"].asUInt64();
						info.posts.emplace_back(postInfo);
						i++;
					}
				}
				info.tid = threadId; //标记数据读取成功了
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
			}
			return info;
		}
		//-------------------------------------删帖信息
		inline bool is_deleted(uint64 id, string type)
		{
			string param = (format("{%%22%s_id%%22:%ld}") % type % id).str();
			string jsonStr = get_delete_info_str(param);
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return false;
			}
			bool isDeleted = false;
			try
			{
				isDeleted = root["output"][(format("del%s_res") % type).str()].size() > 0;
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
				return false;
			}
			return isDeleted;
		}

		inline bool is_thread_deleted(uint64 tid)
		{
			return is_deleted(tid, "thread");
		}

		inline bool is_post_deleted(uint64 pid)
		{
			return is_deleted(pid, "post");
		}

		inline void parse_delete_info(const Json::Value& jsonDelInfo, DeleteInfo& deleteInfo, string type)
		{
			deleteInfo.monitorType = jsonDelInfo["monitor_type"].asString();
			deleteInfo.opUid = UINT64(jsonDelInfo["op_uid"].asString());
			deleteInfo.opTime = UINT64(jsonDelInfo["op_uid"].asString());
			if (type == "thread")
			{
				deleteInfo.tid = UINT64(jsonDelInfo["thread_id"].asString());
			}
			else
			{
				deleteInfo.pid = UINT64(jsonDelInfo["post_id"].asString());
			}
			deleteInfo.isDeleted = true;
		}

		inline DeleteInfo get_delete_info(uint64 id, string type)
		{
			DeleteInfo deleteInfo;
			string param = (format("{%%22%s_id%%22:%ld}") % type % id).str();
			string jsonStr = get_delete_info_str(param);
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return deleteInfo;
			}
			try
			{
				auto& m = root["output"][(format("del%s_res") % type).str()];
				if (m.size() > 0)
				{
					auto& jsonDelInfo = m[m.getMemberNames()[0]];
					parse_delete_info(jsonDelInfo, deleteInfo, type);
				}
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
			}
			return deleteInfo;
		}

		inline DeleteInfo get_thread_delete_info(uint64 tid)
		{
			return get_delete_info(tid, "thread");
		}

		//注意回复信息检索似乎很多被删了得没记录返回 尽管有的有 主题信息还比较准 没看到遗漏
		inline DeleteInfo get_post_delete_info(uint64 pid)
		{
			return get_delete_info(pid, "post");
		}

		inline set<uint64> is_deletes(const vector<uint64>& ids, string type)
		{
			set<uint64> deletedIds;
			string params = join((from(ids)
				>> select([&type](uint64 id) { return (format("{%%22%s_id%%22:%ld}") % type % id).str(); })
				>> to_vector()), ",");
			string jsonStr = get_delete_info_str(params);
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return deletedIds;
			}
			try
			{
				auto& m = root["output"][(format("del%s_res") % type).str()];
				const auto& memberNames = m.getMemberNames();
				for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
				{
					deletedIds.insert(UINT64(*iter));
				}
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
			}
			return deletedIds;
		}

		inline set<uint64> is_threads_deleted(const vector<uint64>& tids)
		{
			return is_deletes(tids, "thread");
		}

		inline set<uint64> is_posts_deleted(const vector<uint64>& pids)
		{
			return is_deletes(pids, "post");
		}

		inline map<uint64, DeleteInfo> get_deletes_info(const vector<uint64>& ids, string type)
		{
			map<uint64, DeleteInfo> deleteInfoMap;
			string params = join((from(ids)
				>> select([&type](uint64 id) { return (format("{%%22%s_id%%22:%ld}") % type % id).str(); })
				>> to_vector()), ",");
			string jsonStr = get_delete_info_str(params);
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return deleteInfoMap;
			}
			try
			{
				auto m = root["output"][(format("del%s_res") % type).str()];
				const auto& memberNames = m.getMemberNames();
				for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
				{
					auto& jsonDelInfo = m[*iter];
					DeleteInfo deletelInfo;
					parse_delete_info(jsonDelInfo, deletelInfo, type);
					deleteInfoMap[UINT64(*iter)] = deletelInfo;
				}
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
			}
			return deleteInfoMap;
		}

		inline map<uint64, DeleteInfo> get_threads_delete_info(const vector<uint64>& tids)
		{
			return get_deletes_info(tids, "thread");
		}

		inline map<uint64, DeleteInfo> get_posts_delete_info(const vector<uint64>& pids)
		{
			return get_deletes_info(pids, "post");
		}
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_GET_PARSED_INFO_H_
