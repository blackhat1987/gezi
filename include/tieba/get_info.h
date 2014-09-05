/**
 *  ==============================================================================
 *
 *          \file   tieba/get_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-24 12:12:39.213334
 *
 *  \Description:  贴吧类接口 通过url 获取json格式内容
 *  ==============================================================================
 */

#ifndef TIEBA_GET_INFO_H_
#define TIEBA_GET_INFO_H_
#include "common_util.h"
#include "curl_util.h"
#include "json/json.h"
#include "random_util.h"

namespace gezi {
	namespace tieba {

		inline string get_info_str(string url, int timeout = -1)
		{
			if (timeout < 0)
			{
				//timeout = PSCONF_(timeout, "tieba.get_info", 1000);
				timeout = 1000;
			}
			CurlUtil curl;
			curl.setTimeout(timeout);
			return curl.get(url);
		}

		//获取帖子信息
		inline string get_posts_info_str(string pids)
		{
			string url = "http://service.tieba.baidu.com/service/post?method=getPostInfo&format=json&post_ids=[" + pids + "]";
			return get_info_str(url);
		}

		inline string get_post_info_str(uint64 pid)
		{
			return get_posts_info_str(STR(pid));
		}

		inline string get_post_info_str(const svec& pids)
		{
			string pids_ = join(pids, ",");

		}
		
		//批量获取帖子内容
		inline string get_posts_info_str(const svec& pids)
		{
			string pids_ = join(pids, ",");
			return get_posts_info_str(pids_);
		}

		inline string get_posts_info_str(const vector<uint64>& pids)
		{
			return get_posts_info_str(convert(pids));
		}

		inline string get_threads_info_str(string tids_, bool need_abstract = false)
		{
			string url;
			url = (format("http://service.tieba.baidu.com/service/post?method=mgetThread&format=json&need_abstract=[%d]&forum_id=0&need_photo_pic=0&need_user_data=0&icon_size=0&need_forum_name=1&call_from=pc&thread_ids=[%s]") % need_abstract % tids_).str();
			return get_info_str(url);
		}

		inline string get_threads_info_str(const svec& tids, bool need_abstract = false)
		{
			string tids_ = gezi::join(tids, ",");
			return get_threads_info_str(tids_, need_abstract);
		}

		inline string get_threads_info_str(const vector<uint64>& tids, bool need_abstract = false)
		{
			return get_threads_info_str(convert(tids), need_abstract);
		}

		inline string get_thread_info_str(uint64 tid, bool need_abstract = false)
		{
			return get_threads_info_str(STR(tid), need_abstract);
		}

		//获取删帖信息
		inline string get_delete_info_str(string pids)
		{
			string url = "http://service.tieba.baidu.com/service/post?method=getDelpostInfo&format=json&post_ids=[" + pids + "]";
			return get_info_str(url);
		}

		template<typename Vec>
		set<uint64> get_deleted_threads(Vec& tids)
		{
			set<uint64> deletedThreads;

			Json::Reader reader;
			Json::Value root;
			string url = "http://service.tieba.baidu.com/service/post?method=getDelpostInfo&post_ids=[$input$]&format=json";

			svec parts;
			for (auto& item : tids)
			{
				string part = "{%22thread_id%22:" + STR(item) + ",%22post_id%22:19821229}";
				parts.push_back(part);
			}

			boost::replace_first(url, "$input$", gezi::join(parts, ","));
			PVAL(url);
			string jsonStr = get_info_str(url);
			PVAL(jsonStr);
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return deletedThreads;
			}

			try
			{
				auto& tds = root["output"]["delthread_res"];
				const auto& member = tds.getMemberNames();
				for (auto iter = member.begin(); iter != member.end(); ++iter)
				{
					deletedThreads.insert(UINT64(*(iter)));
				}
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
			}
			return deletedThreads;
		}

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
			//@TODO 改成使用&format=json这样写起来更方便 不需要%22这些
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
		//获取用户信息

		////20140223 目前看这个接口比较慢 200ms-600ms
		//inline string get_post_info(uint64 pid)
		//{
		//	string section = "tieba.post_info";
		//	//因为有%所以 fromat失败
		//	/*string url = SCONF_(url, "http://service.tieba.baidu.com/service/antiserver?method=antiUrateTrain&req=a:1:{s:7:%22post_id%22;i:%d;}&format=mcpackraw");*/
		//	//	url = (format(url) % pid).str();
		//	//string url = SCONF_(url, "http://service.tieba.baidu.com/service/antiserver?method=antiUrateTrain&req=a:1:{s:7:%22post_id%22;i:$pid$;}&format=mcpackraw");
		//	string url = "http://service.tieba.baidu.com/service/antiserver?method=antiUrateTrain&req=a:1:{s:7:%22post_id%22;i:$pid$;}&format=mcpackraw";
		//	Pval(pid);
		//	boost::replace_first(url, "$pid$", STR(pid));
		//	return get_info(url);
		//}

		//获取用户关注数目 粉丝数目 @TODO 这个接口会被废弃 采用调用统一的用户信息接口?
		inline string get_user_fans(uint64 uid)
		{
			string section = "tieba.user_fans";
			/*	string url = SCONF_(url, (format("http://service.tieba.baidu.com/service/user?method=getUserinfo&user_id=%s&format=json&get_sign=0") % uid).str());*/
			string url = (format("http://service.tieba.baidu.com/service/user?method=getUserinfo&user_id=%s&format=json&get_sign=0") % uid).str();
			return get_info_str(url);
		}

		inline bool get_user_fans(uint64 uid, AnyMap& result)
		{
			Json::Reader reader;
			Json::Value root;
			string json_str = get_user_fans(uid);
			bool ret = reader.parse(json_str, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return false;
			}

			try
			{
				Json::Value& uinfo = root["user_info"][0];
				result["follow_count"] = uinfo["follow_count"].asInt();
				result["followed_count"] = uinfo["followed_count"].asInt();
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
				return false;
			}
			return true;
		}

		inline bool get_user_fans(uint64 uid, int& follow_count, int& followed_count)
		{
			Json::Reader reader;
			Json::Value root;
			string json_str = get_user_fans(uid);
			bool ret = reader.parse(json_str, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail: " << json_str;
				return false;
			}

			try
			{
				Json::Value& uinfo = root["user_info"][0];
				follow_count = uinfo["follow_count"].asInt();
				followed_count = uinfo["followed_count"].asInt();
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
				return false;
			}
			return true;
		}

		//获取整楼的数据
		inline string get_full_posts_info_str(uint64 threadId, int resNum = 100, int offset = 0, int hasComment  =0, uint64 postId = 0)
		{
			string url = (format("http://service.tieba.baidu.com/service/post?method=getFullPostsByThreadId&format=json&thread_id=%ld&res_num=%d&offset=%d&has_comment=%d&post_id=%ld") % threadId % resNum % offset % hasComment % postId).str();
			return get_info_str(url);
		}
	}  //----end of namespace tieba
}  //----end of namespace gezi
#endif  //----end of TIEBA_GET_INFO_H_
