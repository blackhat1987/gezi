/**
 *  ==============================================================================
 *
 *          \file   tieba/info/forum_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-05 14:50:11.677583
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_INFO_FORUM_INFO_H_
#define TIEBA_INFO_FORUM_INFO_H_
#include "tieba/get_info.h"
#include "tieba/info_def.h"
namespace gezi {
	namespace tieba {

		//根据吧名字获取吧id
		inline uint get_forum_id(string forumName)
		{
			uint forumId = 0;
			string jsonStr = get_forum_id_str((format("\"%s\"") % forumName).str());
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			PVAL(jsonStr);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail: " << jsonStr;
				return forumId;
			}
			try
			{
				auto& m = root["forum_id"];
				if (m.size() > 0)
				{
					auto& jsonInfo = m[0];
					forumId = jsonInfo["forum_id"].asUInt();
				}
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail: " << jsonStr;
			}
			return forumId;
		}

		inline vector<uint> get_forum_ids(const svec& forumNames_, bool allowError = true)
		{
			vector<uint> forumIds;
			auto forumNamesVec = split(forumNames_, kMaxRequestCount);
			for (auto& forumNames : forumNamesVec)
			{
				string jsonStr = get_forum_id_str(join(from(forumNames)
					>> select([](string forumName) { return (format("\"%s\"") % forumName).str(); }) >> to_vector(),
					","));
				PVAL(jsonStr);
				Json::Reader reader;
				Json::Value root;
				bool ret = reader.parse(jsonStr, root);
				if (!ret)
				{
					LOG(WARNING) << "json parse fail: " << jsonStr;
					if (!allowError)
					{
						forumIds.clear();
						return forumIds;
					}
					continue;
				}
				try
				{
					auto& m = root["forum_id"];
					for (auto& jsonInfo : m)
					{
						uint forumId = jsonInfo["forum_id"].asUInt();
						forumIds.push_back(forumId); //如果是0表示无效
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << jsonStr;
					if (!allowError)
					{
						forumIds.clear();
						return forumIds;
					}
				}
			}
			return forumIds;
		}

		//根据吧id获取吧名字
		inline string get_forum_name(uint forumId)
		{
			string forumName;
			string jsonStr = get_forum_name_str(forumId);
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return forumName;
			}
			try
			{
				auto& m = root["forum_name"];
				if (m.size() > 0)
				{
					auto& jsonInfo = m[m.getMemberNames()[0]];
					forumName = jsonInfo["forum_name"].asString();
				}
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
			}
			return forumName;
		}

		inline map<string, uint> get_forum_ids_map(const svec& forumNames_)
		{
			map<string, uint> forumIdsMap;
			auto forumNamesVec = split(forumNames_, kMaxRequestCount);
			for (auto& forumNames : forumNamesVec)
			{
				string jsonStr = get_forum_id_str(join(from(forumNames)
					>> select([](string forumName) { return (format("\"%s\"") % forumName).str(); }) >> to_vector(),
					","));
				PVAL(jsonStr);
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
					auto& m = root["forum_id"];
					for (auto& jsonInfo : m)
					{
						uint forumId = jsonInfo["forum_id"].asUInt();
						if (forumId)
						{
							forumIdsMap[jsonInfo["forum_name"].asString()] = forumId;
						}
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << jsonStr;
				}
			}
			return forumIdsMap;
		}

		//安全做法应该是返回map 因为可能某个fid对应没找到数据信息 但是这里默认输入是完全正确的 
		//如果有的没信息对应关系就丢了  @TODO 提供返回map的接口
		//inline vector<string> get_forum_names(const vector<uint>& forumIds_, bool allowError = false)
		//{
		//	svec forumNames;
		//	auto forumIdsVec = gezi::split(forumIds_, kMaxRequestCount);
		//	for (auto& forumIds : forumIdsVec)
		//	{
		//		string jsonStr = get_forum_name_str(forumIds);
		//		Json::Reader reader;
		//		Json::Value root;
		//		bool ret = reader.parse(jsonStr, root);
		//		if (!ret)
		//		{
		//			LOG(WARNING) << "json parse fail: " << jsonStr;
		//			if (!allowError)
		//			{
		//				forumNames.clear();
		//				return forumNames;
		//			}
		//			continue;
		//		}
		//		try
		//		{
		//			auto& m = root["forum_name"];
		//			const auto& memberNames = m.getMemberNames();
		//			typedef decltype(memberNames.begin()) Iter;
		//			map<string, Iter> id2IterMap;
		//			for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
		//			{
		//				id2IterMap[*iter] = iter;
		//			}
		//			for (auto id : forumIds)
		//			{
		//				auto it = id2IterMap.find(STR(id));
		//				if (it == id2IterMap.end())
		//				{
		//					continue;
		//				}
		//				auto iter = it->second; //存在tid不在map中的可能
		//				auto& jsonInfo = m[*iter];
		//				forumNames.push_back(jsonInfo["forum_name"].asString());
		//			}
		//		}
		//		catch (...)
		//		{
		//			LOG(WARNING) << "get json value fail: " << jsonStr;
		//			if (!allowError)
		//			{
		//				forumNames.clear();
		//				return forumNames;
		//			}
		//		}
		//	}
		//	return forumNames;
		//}

		inline map<uint, string> get_forum_names_map(const vector<uint>& forumIds_)
		{
			map<uint, string> forumNamesMap;
			auto forumIdsVec = gezi::split(forumIds_, kMaxRequestCount);
			for (auto& forumIds : forumIdsVec)
			{
				string jsonStr = get_forum_name_str(forumIds);
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
					auto& m = root["forum_name"];
					const auto& memberNames = m.getMemberNames();
					for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
					{
						auto& jsonInfo = m[*iter];
						forumNamesMap[UINT(*iter)] = jsonInfo["forum_name"].asString();
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << jsonStr;
				}
			}
			return forumNamesMap;
		}

		//@TODO 实际中这种和上面注释的get_forum_names哪个更方便 上面那个可以出现错误马上不再进行后续步骤
		//这个方便index 并且批量允许失败设置默认值
		inline vector<string> get_forum_names(const vector<uint>& forumIds)
		{
			svec forumNames;
			map<uint, string> forumNamesMap = get_forum_names_map(forumIds);
			for (auto forumId : forumIds)
			{
				auto iter = forumNamesMap.find(forumId);
				if (iter != forumNamesMap.end())
				{
					forumNames.push_back(iter->second);
				}
				else
				{
					forumNames.push_back("");
				}
			}
			return forumNames;
		}

		//根据吧id获取路径信息
		inline ForumInfo get_forum_info(uint forumId)
		{
			ForumInfo forumInfo;
			string jsonStr = get_forum_info_str(forumId);
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			PVAL(jsonStr);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail: " << jsonStr;
				return forumInfo;
			}
			try
			{
				auto& m = root["output"];
				forumInfo.level1Name = m["level_1_name"].asString();
				forumInfo.level2Name = m["level_2_name"].asString();
				forumInfo.hotValue = m["hot_value"].asUInt();
				forumInfo.rank = m["rank"].asUInt();
				forumInfo.fid = forumId;
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail: " << jsonStr;
			}
			return forumInfo;
		}

		inline ForumInfo get_forum_info(string forumName)
		{
			return get_forum_info(get_forum_id(forumName));
		}

		//有可能有失败情况 但是由于考虑数据输入应该是正确的 不考虑更多处理
		//@TODO 返回map
		inline vector<ForumInfo> get_forums_info(vector<uint> forumIds_, bool allowError = true)
		{
			vector<ForumInfo> forumInfos;
			auto forumIdsVec = gezi::split(forumIds_, kMaxRequestCount);
			for (auto& forumIds : forumIdsVec)
			{
				string jsonStr = get_forums_info_str(forumIds);
				Json::Reader reader;
				Json::Value root;
				bool ret = reader.parse(jsonStr, root);
				if (!ret)
				{
					LOG(WARNING) << "json parse fail: " << jsonStr;
					if (!allowError)
					{
						forumInfos.clear();
						return forumInfos;
					}
					continue;
				}
				try
				{
					auto& m = root["output"];
					const auto& memberNames = m.getMemberNames();
					typedef decltype(memberNames.begin()) Iter;
					map<string, Iter> id2IterMap;
					for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
					{
						id2IterMap[*iter] = iter;
					}
					for (auto id : forumIds)
					{
						auto it = id2IterMap.find(STR(id));
						if (it == id2IterMap.end())
						{
							continue;
						}
						auto iter = it->second; //存在tid不在map中的可能
						auto& jsonInfo = m[*iter];
						ForumInfo forumInfo;
						forumInfo.level1Name = jsonInfo["level_1_name"].asString();
						forumInfo.level2Name = jsonInfo["level_2_name"].asString();
						forumInfo.hotValue = jsonInfo["hot_value"].asUInt();
						forumInfo.rank = jsonInfo["rank"].asUInt();
						forumInfo.fid = UINT(*iter);
						forumInfos.emplace_back(forumInfo);
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << jsonStr;
					if (!allowError)
					{
						forumInfos.clear();
						return forumInfos;
					}
				}
			}
			return forumInfos;
		}

		inline map<uint, ForumInfo> get_forums_info_map(vector<uint> forumIds_)
		{
			map<uint, ForumInfo> forumInfosMap;
			auto forumIdsVec = gezi::split(forumIds_, kMaxRequestCount);
			for (auto& forumIds : forumIdsVec)
			{
				string jsonStr = get_forums_info_str(forumIds);
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
					auto& m = root["output"];
					const auto& memberNames = m.getMemberNames();
					for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
					{
						auto& jsonInfo = m[*iter];
						ForumInfo forumInfo;
						forumInfo.level1Name = jsonInfo["level_1_name"].asString();
						forumInfo.level2Name = jsonInfo["level_2_name"].asString();
						forumInfo.hotValue = jsonInfo["hot_value"].asUInt();
						forumInfo.rank = jsonInfo["rank"].asUInt();
						forumInfo.fid = UINT(*iter);
						forumInfosMap[UINT(*iter)] = forumInfo;
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << jsonStr;
				}
			}
			return forumInfosMap;
		}
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_FORUM_INFO_H_
