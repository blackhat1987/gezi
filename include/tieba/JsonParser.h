/**
 *  ==============================================================================
 *
 *          \file   tieba/JsonParser.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-24 09:18:59.706275
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA__JSON_PARSER_H_
#define TIEBA__JSON_PARSER_H_
#include "json/json.h"
#include "common_util.h"
#include "tieba/common_def.h"
namespace gezi {
	namespace tieba {
	
		class JsonParser
		{
		public:
			//ȡ�õ����ݿ��ܲ�δ���򡣡�

			struct Cmp
			{
				Json::Value& posts;
				string time;

				Cmp(Json::Value& posts_, string time_)
					: posts(posts_), time(time_)
				{

				}

				inline bool operator()(int i, int j)
				{
					return posts[i][time].asUInt64() > posts[j][time].asUInt64();
				}
			};

			static vector<int> sort(Json::Value& posts, string time)
			{
				int len = posts.size();

#ifndef NDEBUG
				if (len > 1)
				{
					if (posts[0]["uid"].asString() != posts[len - 1]["uid"].asString())
					{
						len--;
					}
				}
#endif
				vector<int> indexes(len);
				for (int i = 0; i < len; i++)
				{
					indexes[i] = i;
				}
				std::sort(indexes.begin(), indexes.end(), Cmp(posts, time));
#if __GNUC__ > 3
				return std::move(indexes);
#else
				return indexes;
#endif
			}

			static void getPostInfos(Json::Value& res, HistoryType& m)
			{
				VLOG(3) << "---Getting post infos";
				string section = UrateConf::isOnline() ? "postInfo_Online" : "postInfo";
				string names_ = "contents";
				SCONF(names_);
				string time;
				SCONF(time);
				PVAL(time);
				vector<string> names = gezi::to_vec(names_);
				string in_names_ = "content";
				SCONF(in_names_);
				vector<string> inNames = gezi::to_vec(in_names_);
				PVEC(names);
				PVEC(inNames);

				try
				{
					Json::Value& postInfos = res["postInfo"];
					PVAL(postInfos.size());
					PVAL(postInfos[0]["create_time"]);
					vector<int>indexes = sort(postInfos, time);
					int len = indexes.size();
					PVAL(len);
					//TODO û��ֵ����� ��Ҫ�����ش��� ���� level_1_name �еİ�û����Ŀ��Ϣ ���Ǻ���������� �������null ����Ļ� 
					//���Ӷ�Ӧλ����Ϣ�Ͷ�Ӧ������ ������ʱֻ��mean var ��Ϣ����ν ����adFeature��Ҫ��Ӧ��
					int name_num = names.size();
					for (int i = 0; i < name_num; i++)
					{
						if (contains(&m, names[i]))
						{
							continue;
						}
						m[names[i]] = vector<string>();
						for (int j = 0; j < len; j++)
						{
							string item = postInfos[indexes[j]][inNames[i]].asString();
							PVAL(item);
							if (item != "null")
							{
								m[names[i]].push_back(item);
							}
							else
							{
								if (inNames[i] == "adFeature")
								{
									if (j == 0)
									{//temply fixed ��ǰ�ǵ�ǰ����û��trate��Ϣ ���ܻ��޸� ��ǰ����Ϊ��һ��������500 
										//ע�����Ὣ500 תΪ (1000 - 5000)/1000Ȼ�� 0.5תΪһ��default_value
										m[names[i]].push_back("null");
									}
									else
									{
										break;
									}
								}
								else if (inNames[i] == "title" || inNames[i] == "content")
								{//title ����content ���������� �ÿհ�
									m[names[i]].push_back("");
								}
								else if (inNames[i] == "level_1_name" || inNames[i] == "level_2_name")
								{ //�е����ӿ���û����Ŀ��Ϣ
									m[names[i]].push_back("");
								}
							}
						}
					}
					PVEC(m["adFeatures"]);
					PVEC(m["types"]);
				}
				catch (...)
				{
					LOG(WARNING) << "No post info";
				}
			}

			static void getLikeInfos(Json::Value& res, HistoryType & m)
			{
				VLOG(3) << "---Getting like infos";

				string section = "likeInfo";
				string names_ = "likeLevelIds";
				SCONF(names_);
				vector<string> names = gezi::to_vec(names_);
				PVEC(names);
				string in_names_ = "level_id";
				SCONF(in_names_);
				vector<string> inNames = gezi::to_vec(in_names_);
				PVEC(inNames);

				try
				{
					Json::Value& likeInfos = res["likeInfo"];
					int len = likeInfos.size();
					int name_num = names.size();
					for (int i = 0; i < name_num; i++)
					{
						if (contains(&m, names[i]))
						{
							continue;
						}
						m[names[i]] = vector<string>();
						for (int j = 0; j < len; j++)
						{
							string item = likeInfos[j][inNames[i]].asString();
							if (item != "null")
							{
								m[names[i]].push_back(item);
							}
							else
							{
								LOG(WARNING) << format("In likeInfo find null for the %dth with in name %s") % j % inNames[i];
								break;
							}
						}
					}
#ifndef NDEBUG

					foreach(string name, names)
					{
						PVAL(name);
						PVEC(m[name]);
					}
#endif
				}
				catch (...)
				{
					LOG(WARNING) << "No like info";
					throw ("No like info");
				}
			}

			static void getUserInfos(Json::Value& res, HistoryType & m)
			{
				VLOG(3) << "---Getting user infos";
				string section = "userInfo";
				string names_ = "followCount";
				SCONF(names_);
				PVAL(names_);
				vector<string> names = gezi::to_vec(names_);
				PVEC(names);
				string in_names_ = "follow_count";
				SCONF(in_names_);
				vector<string> inNames = gezi::to_vec(in_names_);
				PVEC(inNames);

				try
				{
					Json::Value& userInfo = res["userInfo"];

					int name_num = names.size();
					for (int i = 0; i < name_num; i++)
					{
						if (contains(&m, names[i]))
						{
							continue;
						}
						m[names[i]] = vector<string>();
						string item = userInfo[inNames[i]].asString();
						if (item != "null")
						{
							m[names[i]].push_back(item);
						}
					}

#ifndef NDEBUG

					foreach(string name, names)
					{
						PVAL(name);
						PVEC(m[name]);
					}
#endif
				}
				catch (...)
				{
					LOG(WARNING) << "No user info";
					throw ("No user info");
				}
			}

			static void getPuserInfos(Json::Value& res, HistoryType & m)
			{
				VLOG(3) << "---Getting puser infos";
				string section = "puserInfo";
				string names_;
				SCONF(names_);
				vector<string> names = gezi::to_vec(names_);
				PVEC(names);
				string in_names_;
				SCONF(in_names_);
				vector<string> inNames = gezi::to_vec(in_names_);
				PVEC(inNames);
				int name_num = names.size();

				try
				{
					Json::Value& userInfo = res["userInfo"]["puserinfo"];

					for (int i = 0; i < name_num; i++)
					{
						if (contains(&m, names[i]))
						{
							continue;
						}
						m[names[i]] = vector<string>();
						string item = userInfo[inNames[i]].asString();
						if (item != "null")
						{
							m[names[i]].push_back(item);
						}
					}

#ifndef NDEBUG

					foreach(string name, names)
					{
						PVAL(name);
						PVEC(m[name]);
					}
#endif
				}
				catch (...)
				{
					LOG(WARNING) << "No puser info";
					throw ("No puser info");
				}
			}

			static void getUrlScores(Json::Value& json, HistoryType & m)
			{
				if (contains(&m, "urlScores"))
				{
					return;
				}
				VLOG(3) << "---Getting url scores";
				m["urlScores"] = vector<string>();
				try
				{
					Json::Value& postInfos = json["postInfo"];
					PVAL(postInfos.size());
					for (int i = 0; i < (int)postInfos.size(); i++)
					{
						vector<string> vec;
						try
						{
							Json::Value& res = postInfos[i]["url"]["rank"];
							Json::Value::Members members(res.getMemberNames());
							for (Json::Value::Members::iterator iter = members.begin(); iter != members.end(); ++iter)
							{
								string name = *iter;
								string item = (format("%s%s%s") % name % SharpSep % res[name].asString()).str();
								vec.push_back(item);
							}

							m["urlScores"].push_back(gezi::join(vec, DollarSep));
						}
						catch (...)
						{
							LOG(WARNING) << "getUrlScores parse fail";
							m["urlScores"].push_back("");
						}
					}
					PVEC(m["urlScores"]);
				}
				catch (...)
				{
					LOG(WARNING) << "No url scores";
					if (contains(&m, ContentsName))
					{
						m["urlScores"].resize(m[ContentsName].size(), "");
					}
					throw ("No url scores");
				}
			}
			//�ⲿ������ ���������� �����쳣 ͨ��ivar������ Ŀǰ���ֵ������� ����gbk���ǲ���gb2312��Χ�ַ������� ���� �������\ ����Ľ���\

			static void getHistory(Json::Value& json, HistoryType & m)
			{
				Json::Value* pres = UrateConf::isOffline() ? &json["res"] : &json;
				if (pres)
				{
					getPostInfos(*pres, m);
					getUserInfos(*pres, m);
					getPuserInfos(*pres, m);
					getLikeInfos(*pres, m);
					getUrlScores(*pres, m);
				}
				else
				{
					throw ("pres is null");
				}
			}

			//ȥ��taginfo����Ĵ���������\u....unicode����

			static string filter(string input)
			{
				//\u0001" \u002"
				string pre_input;
				do
				{
					pre_input = input;
					boost::replace_all(input, "\",", "\",");
				} while (input.length() != pre_input.length());
				do
				{
					pre_input = input;
					boost::replace_all(input, "\",", "\",");
				} while (input.length() != pre_input.length());
				do
				{
					pre_input = input;
					boost::replace_all(input, "\"}", "\"}");
				} while (input.length() != pre_input.length());
				do
				{
					pre_input = input;
					boost::replace_all(input, "\"}", "\"}");
				} while (input.length() != pre_input.length());
				do
				{
					pre_input = input;
					boost::replace_all(input, "\"]", "\"]");
				} while (input.length() != pre_input.length());
				do
				{
					pre_input = input;
					boost::replace_all(input, "\"]", "\"]");
				} while (input.length() != pre_input.length());

				boost::erase_all(input, "\"");
				boost::erase_all(input, "\"");
				boost::erase_all(input, "");
				boost::erase_all(input, "");
				return input;
			}

			//����json��ȡ��ʷ no throw
			static bool getHistory(const string& json_str_, HistoryType& history_)
			{
				return getHistory(json_str_, &history_);
			}
			static bool getHistory(const string& json_str_, HistoryType* history_)
			{
				HistoryType& history = *history_;
				string json_str = filter(json_str_);
				Json::Reader reader;
				Json::Value root;
				bool ret = reader.parse(json_str, root);
				if (!ret)
				{
					LOG(WARNING) << reader.getFormattedErrorMessages();
					//      LOG(WARNING) << "filtered: " << json_str;
					return false;
				}
				try
				{
					getHistory(root, history);
				}
				catch (...)
				{
					LOG(WARNING) << "parse fail: " << json_str.substr(0, std::min((int)json_str.size(), 200));
				}
				return true;
			}
		};
	} //---end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA__JSON_PARSER_H_
