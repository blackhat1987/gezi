/**
 *  ==============================================================================
 *
 *          \file   tieba/info/url_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-07 09:18:31.529123
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_INFO_URL_INFO_H_
#define TIEBA_INFO_URL_INFO_H_

#include "tieba/get_info.h"
#include "tieba/info_def.h"

namespace gezi {
	namespace tieba {

		inline string get_url_info_params_(const vector<string>& urls)
		{
			Json::Value root, url, features;
			Json::FastWriter writer;
			for (auto url : urls)
			{
				features.append(to_utf8(url));
			}
			url["features"] = features;
			root["url"] = url;
			return curl_escape(writer.write(root)).str();
			//return writer.write(root);
		}

		inline map<string, UrlInfo> get_urls_info_map(const vector<string>& urls)
		{
			map<string, UrlInfo> infosMap;
		
			string url = "http://service.tieba.baidu.com/service/urlfeature?method=getFeature&format=json&req=";
			url += get_url_info_params_(urls);
			string jsonStr = get_info_str(url);
			
			PVAL(jsonStr);
			Json::Reader reader;
			Json::Value root;
			bool ret = reader.parse(jsonStr, root);
			if (!ret)
			{
				LOG(WARNING) << "json parse fail";
				return infosMap;
			}
			try
			{
				auto& urlInfo = root["res"]["url"];
				{
					auto& rankInfo = urlInfo["rank"];
					const auto& memberNames = rankInfo.getMemberNames();
					for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
					{
						PVAL(*iter);
						string rank = rankInfo[*iter]["rank"]["ret"].asString();
						infosMap[*iter].rank = rank == "null" ? 0 : FLOAT(rank);
					}
				}
				{
					auto& jumpInfo = urlInfo["jump"];
					const auto& memberNames = jumpInfo.getMemberNames();
					for (auto iter = memberNames.begin(); iter != memberNames.end(); ++iter)
					{
						PVAL(*iter);
						string isJump = jumpInfo[*iter]["isjumpurl"]["ret"].asString();
						infosMap[*iter].isJump = isJump == "null" ? false : BOOL(isJump);
						string jumpRank = jumpInfo[*iter]["jumprank"]["ret"].asString();
						infosMap[*iter].jumRank = jumpRank == "null" ? false : FLOAT(jumpRank);
						infosMap[*iter].content = jumpInfo[*iter]["jumpurlcontent"]["ret"].asString();
					}
				}
				for (auto iter = infosMap.begin(); iter != infosMap.end(); ++iter)
				{
					(iter->second).url = iter->first;
				}
			}
			catch (...)
			{
				LOG(WARNING) << "get json value fail";
			}
			return infosMap;
		}

		//先获取map信息 然后组建vector信息数组 如果某个url没有信息 填充默认信息即可
		inline vector<UrlInfo> get_urls_info(const vector<string>& urls)
		{
			vector<UrlInfo> infos;
			map<string, UrlInfo> infosMap = get_urls_info_map(urls);
			for (auto& url : urls)
			{
				auto iter = infosMap.find(url);
				if (iter != infosMap.end())
				{
					infos.push_back(iter->second);
				}
				else
				{
					infos.push_back(UrlInfo());
				}
			}
			return infos;
		}

		inline UrlInfo get_url_info(string url)
		{
			auto infos = get_urls_info(vector<string>({ url }));
			return infos.empty() ? UrlInfo() : infos[0];
		}

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_URL_INFO_H_
