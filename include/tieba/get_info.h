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
			AutoTimer timer("CurlFetchUrl:" + url);
			if (timeout < 0)
			{
				//timeout = PSCONF_(timeout, "tieba.get_info", 1000);
				timeout = 1000;
			}
			CurlUtil curl;
			curl.setTimeout(timeout);
			return curl.get(url);
		}
		
		//not work don't use it use next function below
		inline string sget_info_str(string url, int timeout = -1)
		{
			if (timeout < 0)
			{
				//timeout = PSCONF_(timeout, "tieba.get_info", 1000);
				timeout = 1000;
			}
			CurlUtil curl;
			url = curl.escape(to_utf8(url)).str();
			curl.setTimeout(timeout);
			return curl.get(url);
		}


		inline string get_info_str(CurlUtil& curl, string url, int timeout = -1)
		{
			if (timeout < 0)
			{
				//timeout = PSCONF_(timeout, "tieba.get_info", 1000);
				timeout = 1000;
			}
			
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

		
		//获取用户信息

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
	
		//吧相关
		inline string get_forum_id_str(string forumNames)
		{
			forumNames = curl_escape(to_utf8(forumNames)).str();
			string url = "http://service.tieba.baidu.com/service/forum?method=getFidByFname&format=json&query_words=[" + forumNames + "]";
			PVAL(url);
			return get_info_str(url);
		}

		inline string get_forum_name_str(string params)
		{
			string url = "http://service.tieba.baidu.com/service/forum?method=getFnameByFid&format=json&forum_id=[" + params + "]";
			PVAL(url);
			return get_info_str(url);
		}

		inline string get_forum_name_str(uint forumId)
		{
			return get_forum_name_str(STR(forumId));
		}

		inline string get_forum_name_str(const vector<uint>& forumIds)
		{
			string params = join(convert(forumIds), ",");
			return get_forum_name_str(params);
		}
	

		inline string get_forum_info_str(string params)
		{
			string url = "http://service.tieba.baidu.com/service/forum?method=mgetForumDir&format=json&forum_id=[" + params + "]";
			PVAL(url);
			return get_info_str(url);
		}

		inline string get_forum_info_str(uint forumId)
		{
			string params = STR(forumId);
			string url = "http://service.tieba.baidu.com/service/forum?method=getForumDir&format=json&forum_id=" + params;
			PVAL(url);
			return get_info_str(url);
		}

		inline string get_forums_info_str(const vector<uint>& forumIds)
		{
			string params = join(convert(forumIds), ",");
			string url = "http://service.tieba.baidu.com/service/forum?method=mgetForumDir&format=json&forum_id=[" + params + "]";
			PVAL(url);
			return get_info_str(url);
		}
	}  //----end of namespace tieba
}  //----end of namespace gezi
#endif  //----end of TIEBA_GET_INFO_H_
