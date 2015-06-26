/**
 *  ==============================================================================
 *
 *          \file   tieba/get_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-24 12:12:39.213334
 *
 *  \Description:  ������ӿ� ͨ��url ��ȡjson��ʽ����
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
		static const char* const kTiebaGetInfoName = "Tieba.GetInfo";
		inline void get_field_method(string url, string& field, string& method)
		{
			//http://service.tieba.baidu.com/service/post?method=mgetThread&
			string host = "http://service.tieba.baidu.com/service/";
			string body = url.substr(host.length());
			body = body.substr(0, body.find('&'));
			split(body, "?method=", field, method);
			PVAL2(field, method);
		}

		inline string get_info_str(string url, int timeout = -1)
		{
			AutoTimer timer("CurlFetchUrl:" + url);
			if (timeout < 0)
			{
				timeout = 5000;
				PSCONF(timeout, kTiebaGetInfoName);
			}

			bool isOnline = false;
			PSCONF(isOnline, "Global");
			if (isOnline)
			{
				bool needFetch = false;
				string field, method;
				get_field_method(url, field, method);
				string name = field + "_" + method;
				name += "_needFetch";
				PSCONF_WITHNAME(needFetch, name, kTiebaGetInfoName);
				if (!needFetch)
				{
					return ""; //@TODO fetch from SharedJson
				}
			}

			CurlUtil curl;
			curl.setTimeout(timeout);
			return curl.get(url);
		}

		////not work don't use it use next function below
		//inline string sget_info_str(string url, int timeout = -1)
		//{
		//	if (timeout < 0)
		//	{
		//		//timeout = PSCONF_(timeout, "tieba.get_info", 1000);
		//		timeout = 1000;
		//	}
		//	CurlUtil curl;
		//	url = curl.escape(to_utf8(url)).str();
		//	curl.setTimeout(timeout);
		//	return curl.get(url);
		//}


		/*	inline string get_info_str(CurlUtil& curl, string url, int timeout = -1)
			{
			if (timeout < 0)
			{
			timeout = 1000;
			}

			curl.setTimeout(timeout);
			return curl.get(url);
			}*/

		//��ȡ������Ϣ
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

		//������ȡ��������
		inline string get_posts_info_str(const svec& pids)
		{
			string pids_ = join(pids, ",");
			return get_posts_info_str(pids_);
		}

		inline string get_posts_info_str(const vector<uint64>& pids)
		{
			return get_posts_info_str(convert(pids));
		}

		inline string get_threads_info_str(string tids_, bool need_abstract = true)
		{
			string url;
			url = (boost::format("http://service.tieba.baidu.com/service/post?method=mgetThread&format=json&need_abstract=%d&forum_id=0&need_photo_pic=0&need_user_data=0&icon_size=0&need_forum_name=1&call_from=pc&thread_ids=[%s]") % need_abstract % tids_).str();
			return get_info_str(url);
		}

		inline string get_threads_info_str(const svec& tids, bool need_abstract = true)
		{
			string tids_ = gezi::join(tids, ",");
			return get_threads_info_str(tids_, need_abstract);
		}

		inline string get_threads_info_str(const vector<uint64>& tids, bool need_abstract = true)
		{
			return get_threads_info_str(convert(tids), need_abstract);
		}

		inline string get_thread_info_str(uint64 tid, bool need_abstract = true)
		{
			return get_threads_info_str(STR(tid), need_abstract);
		}

		//��ȡɾ����Ϣ
		inline string get_delete_info_str(string pids)
		{
			string url = "http://service.tieba.baidu.com/service/post?method=getDelpostInfo&format=json&post_ids=[" + pids + "]";
			return get_info_str(url);
		}


		//��ȡ�û���Ϣ

		//��ȡ�û���ע��Ŀ ��˿��Ŀ @TODO ����ӿڻᱻ���� ���õ���ͳһ���û���Ϣ�ӿ�?
		inline string get_user_fans(uint64 uid)
		{
			string section = "tieba.user_fans";
			/*	string url = SCONF_(url, (boost::format("http://service.tieba.baidu.com/service/user?method=getUserinfo&user_id=%s&format=json&get_sign=0") % uid).str());*/
			string url = (boost::format("http://service.tieba.baidu.com/service/user?method=getUserinfo&user_id=%s&format=json&get_sign=0") % uid).str();
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

		//��ȡ��¥������
		inline string get_full_posts_info_str(uint64 threadId, int resNum = 100, int offset = 0, int hasComment = 0, uint64 postId = 0)
		{
			string url = (boost::format("http://service.tieba.baidu.com/service/post?method=getFullPostsByThreadId&format=json&thread_id=%ld&res_num=%d&offset=%d&has_comment=%d&post_id=%ld") % threadId % resNum % offset % hasComment % postId).str();
			return get_info_str(url);
		}

		//�����
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

		// ���� ͼƬ�������
		inline string get_img_info_str(uint64 pid, int64 createTime)
		{
			string stime;
			tm *createtime;
			time_t ltime = createTime;
			createtime = localtime(&ltime);
			string month = STR(createtime->tm_mon + 1);
			if (createtime->tm_mon < 9)
				month = "0" + month;
			string day = STR(createtime->tm_mday);
			if (createtime->tm_mday < 10)
				day = "0" + day;
			string year = STR(createtime->tm_year + 1900);
			stime = year + month + day;
			string url = "http://service.tieba.baidu.com/service/uegimgfea?method=getImgByPostId&format=json&req={%22postId%22:" + STR(pid) + ",%22date%22:" + stime + "}";
			PVAL(url);
			return get_info_str(url);
		}

		template<typename InfoType, typename Func>
		inline InfoType try_get_info(uint64 id, Func func, string historyDir, bool forceFetch = false, bool useFetch = true,
			string suffix = "", bool retry = true)
		{
			InfoType info;
			try_create_dir(historyDir);
			string end = suffix.empty() ? ".json" : "." + suffix + ".json";
			string historyFile = historyDir + "/" + STR(id) + end;
			if (!forceFetch)
			{
				serialize_util::load_json(historyFile, info);
			}
			if (useFetch)
			{
				if (!info.IsValid())
				{
					info = func(id);
					if (info.IsValid())
					{
						serialize_util::save_json(info, historyFile);
					}
					else
					{ //������һ�λ�ȡ
						LOG(WARNING) << "Fetch info fail try to fetch again";
						if (retry)
						{
							info = func(id);
							if (info.IsValid())
							{
								serialize_util::save_json(info, historyFile);
							}
							else
							{
								LOG(WARNING) << "Retry still fail";
							}
						}
					}
				}
			}
			return info;
		}

		template<typename IdType, typename InfosType, typename Func>
		void try_get_infos_(const vector<IdType>& ids, InfosType& infos, Func func, string historyDir, string historyName,
			bool forceFetch = false, bool useFetch = true, string suffix = "")
		{
			string end = suffix.empty() ? ".json" : "." + suffix + ".json";
			string historyFile = historyDir + "/" + historyName + end;
			if (!forceFetch)
			{
				serialize_util::load_json(historyFile, infos);
			}
			if (useFetch)
			{
				if (infos.empty())
				{
					infos = func(ids);
					if (!infos.empty())
					{
						serialize_util::save_json(infos, historyFile);
					}
				}
			}
		}

		template<typename InfoType, typename Func>
		inline vector<InfoType> try_get_infos(const vector<uint64>& ids, Func func, string historyDir, string historyName,
			bool forceFetch = false, bool useFetch = true, string suffix = "")
		{
			vector<InfoType> infos;
			try_get_infos_<uint64, vector<InfoType> >(ids, infos, func, historyDir, historyName, forceFetch, useFetch, suffix);
			return infos;
		}

		template<typename IdType, typename InfoType, typename Func>
		inline map<IdType, InfoType> try_get_infos_map(const vector<IdType>& ids, Func func, string historyDir, string historyName,
			bool forceFetch = false, bool useFetch = true, string suffix = "")
		{
			map<IdType, InfoType> infos;
			try_get_infos_<IdType, map<IdType, InfoType> >(ids, infos, func, historyDir, historyName, forceFetch, useFetch, suffix);
			return infos;
		}


	}  //----end of namespace tieba
}  //----end of namespace gezi
#endif  //----end of TIEBA_GET_INFO_H_
