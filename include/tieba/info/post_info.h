/**
 *  ==============================================================================
 *
 *          \file   tieba/info/post_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-05 11:33:57.645486
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_INFO_POST_INFO_H_
#define TIEBA_INFO_POST_INFO_H_

#include "tieba/get_info.h"
#include "tieba/info_def.h"

namespace gezi {
	namespace tieba {
		//--------------------------------------post��Ϣ
		//��ȡ���ӱ�������
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
			info.fid = m["forum_id"].asUInt();
			info.forumName = m["word"].asString();
			info.ip = m["ip"].asUInt64();
			//info.tid = m["thread_id"].asUInt64(); //Type is not convertible to UInt64 @TODO ��˵Ӧ��֧��ֱ��ת�ɡ���
			info.tid = UINT64(m["thread_id"].asString());
			info.uname = m["username"].asString();
			info.time = m["now_time"].asUInt64();
		}

		//@TODO ��������ӿڵ�has_ext��ȡlbs��Ϣ ʡ��+����  �� ����ɾ����Ϣ�ȵ� ��ô���룿
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

		inline vector<PostInfo> get_posts_info(const vector<uint64>& pids_, bool allowError = true)
		{
			vector<PostInfo> resultVec;

			auto pidsVec = gezi::split(pids_, kMaxRequestCount);

			for (auto& pids : pidsVec)
			{
				string jsonStr = get_posts_info_str(pids);

				Json::Reader reader;
				Json::Value root;
				bool ret = reader.parse(jsonStr, root);
				if (!ret)
				{
					LOG(WARNING) << "json parse fail: " << jsonStr;
					if (!allowError)
					{
						resultVec.clear();
						return resultVec;
					}
					continue;
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
					LOG(WARNING) << "get json value fail: " << jsonStr;
					if (!allowError)
					{
						resultVec.clear();
						return resultVec;
					}
				}
			}
			return resultVec;
		}
	} //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_POST_INFO_H_
