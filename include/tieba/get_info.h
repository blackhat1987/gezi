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

namespace gezi {
	namespace tieba {
		inline string get_info(string url, int timeout = -1)
		{
			if (timeout < 0)
			{
				timeout = PSCONF_(timeout, "tieba.get_info", 1000);
			}
			CurlUtil curl;
			curl.setTimeout(timeout);
			return curl.get(url);
		}


		//��ȡ��������
		inline string get_post_info(svec pids)
		{
			string pids_ = gezi::join(pids, ",");
			string url = (format("http://service.tieba.baidu.com/service/antiserver?method=antiGetRscInfo&post_ids=%s&format=mcpackraw")%pids_).str();

			Pval(url);

			return get_info(url);
		}
		//��ȡ�û���Ϣ

		////20140223 Ŀǰ������ӿڱȽ��� 200ms-600ms
		//inline string get_post_info(uint64 pid)
		//{
		//	string section = "tieba.post_info";
		//	//��Ϊ��%���� fromatʧ��
		//	/*string url = SCONF_(url, "http://service.tieba.baidu.com/service/antiserver?method=antiUrateTrain&req=a:1:{s:7:%22post_id%22;i:%d;}&format=mcpackraw");*/
		//	//	url = (format(url) % pid).str();
		//	//string url = SCONF_(url, "http://service.tieba.baidu.com/service/antiserver?method=antiUrateTrain&req=a:1:{s:7:%22post_id%22;i:$pid$;}&format=mcpackraw");
		//	string url = "http://service.tieba.baidu.com/service/antiserver?method=antiUrateTrain&req=a:1:{s:7:%22post_id%22;i:$pid$;}&format=mcpackraw";
		//	Pval(pid);
		//	boost::replace_first(url, "$pid$", STR(pid));
		//	return get_info(url);
		//}

		//��ȡ�û���ע��Ŀ ��˿��Ŀ
		inline string get_user_fans(uint64 uid)
		{
			string section = "tieba.user_fans";
			string url = SCONF_(url, (format("http://service.tieba.baidu.com/service/user?method=getUserinfo&user_id=%s&format=json&get_sign=0") % uid).str());
			return get_info(url);
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
	}  //----end of namespace tieba
}  //----end of namespace gezi
#endif  //----end of TIEBA_GET_INFO_H_
