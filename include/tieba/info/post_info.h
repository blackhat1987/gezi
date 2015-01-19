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
#include "tools/content_process.h"
#include "tieba/info/url_info.h"

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
			info.forumId = m["forum_id"].asUInt();
			info.forumName = m["word"].asString();
			info.ip = m["ip"].asUInt64();
			//info.tid = m["thread_id"].asUInt64(); //Type is not convertible to UInt64 json里面是“”string类型
			info.threadId = UINT64(m["thread_id"].asString());
			info.userId = m["user_id"].asUInt();
			info.userName = m["username"].asString();
			info.createTime = m["now_time"].asInt64();
			if (m.isMember("quote"))
			{
				auto& jsonQuote = m["quote"];
				info.quoteInfo.postId = UINT64(jsonQuote["post_id"].asString());
				info.quoteInfo.userName = jsonQuote["uname"].asString();
				info.quoteInfo.userId = jsonQuote["uid"].asUInt();
				info.quoteInfo.ip = jsonQuote["ip"].asUInt64();
				info.quoteInfo.content = jsonQuote["content"].asString();
			}
			info.postId = UINT64(m["post_id"].asString());
		}

		//没有lbs等信息
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
			info.postId = pid;
			return info;
		}

		inline ExtendedPostInfo get_extended_post_info(uint64 pid)
		{
			ExtendedPostInfo info;
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

			info.urls = get_urls(info.content);
			info.urlInfoMap = get_urls_info_map(info.urls);
			info.postId = pid;
			return info;
		}

		inline vector<PostInfo> get_posts_info(const vector<uint64>& pids_, bool allowError = true)
		{
			vector<PostInfo> resultVec;

			auto pidsVec = gezi::split(pids_, kMaxRequestCount * 0.5);

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
						//info.postId = pids[i++];
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

		inline map<uint64, PostInfo> get_posts_info_map(const vector<uint64>& pids_)
		{
			map<uint64, PostInfo> resultMap;

			auto pidsVec = gezi::split(pids_, kMaxRequestCount * 0.5);

			for (auto& pids : pidsVec)
			{
				string jsonStr = get_posts_info_str(pids);

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
					int i = 0;
					for (const auto& m : root["output"])
					{
						PostInfo info;
						parse_post_info(m, info);
						//info.postId = pids[i++];
						resultMap[info.postId] = info;
					}
				}
				catch (...)
				{
					LOG(WARNING) << "get json value fail: " << jsonStr;
				}
			}
			return resultMap;
		}

		inline void parse_img_info(const Json::Value& m, ImgInfo& info)
		{
			info.imgCount = m.size();
			for (int i = 0; i < m.size(); i++)
			{
				info.color_rate.push_back(INT(m[i]["rate_color"].asString()));
				info.gameporn_rate.push_back(INT(m[i]["rate_gameporn"].asString()));
				info.ocr_img.push_back(m[i]["ocr_img"].asString());
				info.porn_rate.push_back(INT(m[i]["rate_porn_idl"].asString()));
				info.simi_rate.push_back(INT(m[i]["rate_simi_idl"].asString()));
				info.text_ratio.push_back(INT(m[i]["ratio_text"].asString()));
				info.textbox_num.push_back(INT(m[i]["num_textbox"].asString()));
			}
		}

		inline ImgInfo get_img_info(uint64 pid, int64 createTime)
		{
			ImgInfo info;
			info.pid = pid;
			string jsonStr = get_img_info_str(pid, createTime);
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "Img json parse fail";
				return info;
			}
			try
			{
				const auto& m = root["res"]["imgfeaInfo"];
				if (m.isNull())
					return info;
				else
					parse_img_info(m, info);
			}
			catch (...)
			{
				LOG(WARNING) << "get img json value fail";
				return info;
			}
			return info;
		}

	} //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_POST_INFO_H_
