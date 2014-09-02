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

	//批量获取
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
				const auto& member = m.getMemberNames();
				for (auto iter = member.begin(); iter != member.end(); ++iter)
				{
					ThreadInfo node;
					node.tid = UINT64(*iter);
					node.title = m[*iter]["title"].asString();
					node.uid = m[*iter]["user_id"].asUInt64();
					node.ip = m[*iter]["user_ip"].asUInt64();
					node.fid = m[*iter]["forum_id"].asUInt64();
					node.pid = m[*iter]["first_post_id"].asUInt64();
					node.isDeleted = m[*iter]["is_deleted"].asBool();
					node.time = m[*iter]["last_modified_time"].asUInt64();
					node.forumName = m[*iter]["forum_name"].asString();
					if (need_abstract)
					{
						node.content = m[*iter]["abstract"].asString();
						node.hasMedia = !m[*iter]["media"].empty();
					}
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
}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_GET_PARSED_INFO_H_
