/**
 *  ==============================================================================
 *
 *          \file   tieba/info/delete_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-05 11:34:07.437054
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_INFO_DELETE_INFO_H_
#define TIEBA_INFO_DELETE_INFO_H_

#include "tieba/get_info.h"
#include "tieba/info_def.h"

namespace gezi {
	namespace tieba {
		//-------------------------------------删帖信息
		inline bool is_deleted(uint64 id, string type)
		{
			string param = (boost::format("{%%22%s_id%%22:%ld}") % type % id).str();
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
				isDeleted = root["output"][(boost::format("del%s_res") % type).str()].size() > 0;
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

		inline void parse_delete_info_(const Json::Value& jsonDelInfo, DeleteInfo& deleteInfo, string type)
		{
			deleteInfo.monitorType = jsonDelInfo["monitor_type"].asString();
			deleteInfo.opUid = UINT64(jsonDelInfo["op_uid"].asString());
			deleteInfo.opTime = INT64(jsonDelInfo["op_uid"].asString());
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
			//多一个%表示escape
			string param = (boost::format("{%%22%s_id%%22:%ld}") % type % id).str();
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
				auto& m = root["output"][(boost::format("del%s_res") % type).str()];
				if (m.size() > 0)
				{
					auto& jsonDelInfo = m[m.getMemberNames()[0]];
					parse_delete_info_(jsonDelInfo, deleteInfo, type);
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

		inline set<uint64> is_deletes(const vector<uint64>& ids_, string type, bool allowError = true)
		{
			set<uint64> deletedIds;
			auto idsVec = gezi::split(ids_, kMaxRequestCount * 0.5);
			for (auto& ids : idsVec)
			{
				string params = join((from(ids)
					>> select([&type](uint64 id) { return (boost::format("{%%22%s_id%%22:%ld}") % type % id).str(); })
					>> to_vector()), ",");
				string jsonStr = get_delete_info_str(params);
				Json::Reader reader;
				Json::Value root;
				bool ret = reader.parse(jsonStr, root);
				if (!ret)
				{
					LOG(WARNING) << "json parse fail: " << params << "\t" << jsonStr;
					if (!allowError)
					{
						deletedIds.clear();
						return deletedIds;
					}
					continue;
				}
				try
				{
					auto& m = root["output"][(boost::format("del%s_res") % type).str()];
					const auto& memberNames = m.getMemberNames();
					for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
					{
						deletedIds.insert(UINT64(*iter));
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << params << "\t" << jsonStr;
					if (!allowError)
					{
						deletedIds.clear();
						return deletedIds;
					}
				}
			}
			return deletedIds;
		}

		inline set<uint64> is_threads_deleted(const vector<uint64>& tids, bool allowError = true)
		{
			return is_deletes(tids, "thread", allowError);
		}

		inline set<uint64> get_deleted_threads(const vector<uint64>& tids, bool allowError = true)
		{
			return is_deletes(tids, "thread", allowError);
		}

		inline set<uint64> is_posts_deleted(const vector<uint64>& pids, bool allowError = true)
		{
			return is_deletes(pids, "post", allowError);
		}

		inline set<uint64> get_deleted_posts(const vector<uint64>& pids, bool allowError = true)
		{
			return is_deletes(pids, "post", allowError);
		}

		inline map<uint64, DeleteInfo> get_deletes_info(const vector<uint64>& ids_, string type, bool allowError = true)
		{
			map<uint64, DeleteInfo> deleteInfoMap;
			auto idsVec = gezi::split(ids_, kMaxRequestCount * 0.5);
			for (auto& ids : idsVec)
			{
				string params = join((from(ids)
					>> select([&type](uint64 id) { return (boost::format("{%%22%s_id%%22:%ld}") % type % id).str(); })
					>> to_vector()), ",");
				string jsonStr = get_delete_info_str(params);
				Json::Reader reader;
				Json::Value root;
				bool ret = reader.parse(jsonStr, root);
				if (!ret)
				{
					LOG(WARNING) << "json parse fail: " << jsonStr;
					if (!allowError)
					{
						deleteInfoMap.clear();
						return deleteInfoMap;
					}
					continue;
				}
				try
				{
					auto m = root["output"][(boost::format("del%s_res") % type).str()];
					const auto& memberNames = m.getMemberNames();
					for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
					{
						auto& jsonDelInfo = m[*iter];
						DeleteInfo deletelInfo;
						parse_delete_info_(jsonDelInfo, deletelInfo, type);
						deleteInfoMap[UINT64(*iter)] = deletelInfo;
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << jsonStr;
					if (!allowError)
					{
						deleteInfoMap.clear();
						return deleteInfoMap;
					}
				}
			}
			return deleteInfoMap;
		}

		inline map<uint64, DeleteInfo> get_threads_delete_info(const vector<uint64>& tids, bool allowError = true)
		{
			return get_deletes_info(tids, "thread", allowError);
		}

		inline map<uint64, DeleteInfo> get_posts_delete_info(const vector<uint64>& pids, bool allowError = true)
		{
			return get_deletes_info(pids, "post", allowError);
		}

		//rsc 17006实时删帖使用 随机选取50个 查询是否主题或者回复被删除
		inline int get_posts_delete_info(const vector<uint64>& pids, const vector<uint64>& tids, int maxCount = 50)
		{
			Json::Reader reader;
			Json::Value root;
			string url = "http://service.tieba.baidu.com/service/post?method=getDelpostInfo&post_ids=[$input$]&format=json";

			int total = std::min(pids.size(), tids.size());
			bool needRandom = total > maxCount;
			int len = std::min(total, maxCount);

			vector<string> parts;
			if (!needRandom)
			{
				for (int i = 0; i < len; i++)
				{
					string part = "{%22thread_id%22:" + STR(tids[i]) + ",%22post_id%22:" + STR(pids[i]) + "}";
					parts.push_back(part);
				}
			}
			else
			{
				RandomRange range(total);
				for (int i = 0; i < len; i++)
				{
					int idx = range.Next();
					string part = "{%22thread_id%22:" + STR(tids[idx]) + ",%22post_id%22:" + STR(pids[idx]) + "}";
					parts.push_back(part);
				}
			}

			boost::replace_first(url, "$input$", gezi::join(parts, ","));
			PVAL(url);
			string jsonStr = get_info_str(url);
			PVAL(jsonStr);
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return 0;
			}

			int pds = 0, tds = 0;
			try
			{
				pds = root["output"]["delpost_res"].size();
				tds = root["output"]["delthread_res"].size();
				PVAL2(pds, tds);
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
				return 0;
			}
			return std::max(pds, tds);
		}

		inline bool get_post_deleted_info(uint64 pid, uint64 tid, bool& isPostDeleted, bool& isThreadDeleted)
		{
			Json::Reader reader;
			Json::Value root;
			string url = "http://service.tieba.baidu.com/service/post?method=getDelpostInfo&post_ids=[{%22thread_id%22:$tid$,%22post_id%22:$pid$}]&format=json";
			boost::replace_first(url, "$pid$", STR(pid));
			boost::replace_first(url, "$tid$", STR(tid));
			string jsonStr = get_info_str(url);
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return false;
			}

			try
			{
				isPostDeleted = root["output"]["delpost_res"].size() > 0;
				isThreadDeleted = root["output"]["delthread_res"].size() > 0;
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
				return false;
			}
			return true;
		}
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_DELETE_INFO_H_
