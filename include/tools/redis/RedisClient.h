/**
 *  ==============================================================================
 *
 *          \file   RedisClient.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-08 12:24:45.541096
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef REDIS_CLIENT_H_
#define REDIS_CLIENT_H_
#include "RedisClientManager.h"
#include "common_util.h"
namespace gezi {

	class RedisClient
	{
	public:
		RedisClient()
		{

		}

		RedisClient(string confFile, string confDir = "./conf")
		{
			Init(confFile, confDir);
		}

		~RedisClient()
		{
			_clientManager.destroy_client(_client);
			_client = NULL;
			_clientManager.close();
		}

		int Init(string confFile = "redis_client.conf", string confDir = "./conf")
		{
			int ret = _clientManager.init(confDir.c_str(), confFile.c_str());
			if (ret != 0)
			{
				return ret;
			}
			_client = _clientManager.create_client();
			if (_client == NULL)
			{
				return -1;
			}
			return 0;
		}

		store::RedisClient* init(string confFile = "redis_client.conf", string confDir = "./conf")
		{
			int ret = _clientManager.init(confDir.c_str(), confFile.c_str());
			CHECK_EQ(ret, 0);
			_client = _clientManager.create_client();
			return _client;
		}

		store::RedisClient* GetClient()
		{
			return _client;
		}

		//取最前N个，内部可能需要分段取，如果所有的段都是正确的 才返回0
		int ZrangeFirstNElementWithScores(string key, int num, vector<string>& values, vector<double>& scores, int step = 200, bool allowError = true)
		{
			store::ss* valueVec;
			double* scoreVec;
			int ret = 0, outNum = 0, finalRet;
			for (int start = 0; start < num; start += step)
			{
				int nowCount = std::min(step, num - start);
				ret = _client->zrange_withscores(key.c_str(), start, start + nowCount - 1, valueVec, scoreVec, outNum);
				if (ret != 0)
				{
					finalRet = ret;
					if (!allowError)
					{
						return ret;
					}
					continue;
				}
				for (int i = 0; i < outNum; i++)
				{
					string value = valueVec[i].str;
					values.push_back(value);
					scores.push_back(scoreVec[i]);
				}
				if (outNum < nowCount)
				{
					break;
				}
			}
			return finalRet;
		}

		template<typename Func>
		int ZrangeFirstNElementWithScores(string key, int num, vector<string>& values, vector<double>& scores, Func func, int step = 200, bool allowError = true)
		{
			store::ss* valueVec;
			double* scoreVec;
			int ret = 0, outNum = 0, finalRet;
			for (int start = 0; start < num; start += step)
			{
				int nowCount = std::min(step, num - start);
				ret = _client->zrange_withscores(key.c_str(), start, start + nowCount - 1, valueVec, scoreVec, outNum);
				if (ret != 0)
				{
					finalRet = ret;
					if (!allowError)
					{
						return ret;
					}
					continue;
				}
				for (int i = 0; i < outNum; i++)
				{
					string value = valueVec[i].str;
					values.push_back(value);
					scores.push_back(func(scoreVec[i]));
				}
				if (outNum < nowCount)
				{
					break;
				}
			}
			return finalRet;
		}

		template<typename Func>
		int ZrangeFirstNElementWithScores(string key, int num, Func func, int step = 200, bool allowError = true)
		{
			store::ss* valueVec;
			double* scoreVec;
			int ret = 0, outNum = 0, finalRet;
			for (int start = 0; start < num; start += step)
			{
				int nowCount = std::min(step, num - start);
				ret = _client->zrange_withscores(key.c_str(), start, start + nowCount - 1, valueVec, scoreVec, outNum);
				if (ret != 0)
				{
					finalRet = ret;
					if (!allowError)
					{
						return ret;
					}
					continue;
				}
				for (int i = 0; i < outNum; i++)
				{
					string value = valueVec[i].str;
					double score = scoreVec[i];
					func(value, score);
				}
				if (outNum < nowCount)
				{
					break;
				}
			}
			return finalRet;
		}

		template<typename Func>
		int ZrangeFirstNElementWithScoresIf(string key, int num, Func func, int step = 200, bool allowError = true)
		{
			store::ss* valueVec;
			double* scoreVec;
			int ret = 0, outNum = 0, finalRet;
			bool needStop = false;
			for (int start = 0; start < num; start += step)
			{
				int nowCount = std::min(step, num - start);
				ret = _client->zrange_withscores(key.c_str(), start, start + nowCount - 1, valueVec, scoreVec, outNum);
				if (ret != 0)
				{
					finalRet = ret;
					if (!allowError)
					{
						return ret;
					}
					continue;
				}
				for (int i = 0; i < outNum; i++)
				{
					string value = valueVec[i].str;
					double score = scoreVec[i];
					if (!func(value, score))
					{
						needStop = true;
						break;
					}
				}
				if (needStop || outNum < nowCount)
				{
					break;
				}
			}
			return finalRet;
		}

		int ZrangeWithScores(string key, int first, int last, vector<string>& values, vector<double>& scores)
		{
			store::ss* valueVec;
			double* scoreVec;
			int outNum = 0;
			int ret = _client->zrange_withscores(key.c_str(), first, last, valueVec, scoreVec, outNum);
			if (ret == 0)
			{
				for (int i = 0; i < outNum; i++)
				{
						string result = valueVec[i].str;
						values.push_back(result);
						scores.push_back(scoreVec[i]);
				}
			}
			return ret;
		}

		template<typename Func>
		int ZrangeWithScores(string key, int first, int last, vector<string>& values, vector<double>& scores, Func func)
		{
			store::ss* valueVec;
			double* scoreVec;
			int outNum = 0;
			int ret = _client->zrange_withscores(key.c_str(), first, last, valueVec, scoreVec, outNum);
			if (ret == 0)
			{
				for (int i = 0; i < outNum; i++)
				{
					string value = valueVec[i].str;
					double score = scoreVec[i];
					values.push_back(value);
					scores.push_back(func(score));
				}
			}
			return ret;
		}

		template<typename Func>
		int ZrangeWithScores(string key, int first, int last, Func func)
		{
			store::ss* valueVec;
			double* scoreVec;
			int outNum = 0;
			int ret = _client->zrange_withscores(key.c_str(), first, last, valueVec, scoreVec, outNum);
			if (ret == 0)
			{
				for (int i = 0; i < outNum; i++)
				{
					string value = valueVec[i].str;
					double score = scoreVec[i];
					Func(value, score);
				}
			}
			return ret;
		}

		int Zrange(string key, int first, int last, vector<string>& values)
		{
			store::ss* valueVec;
			double* scoreVec;
			int outNum = 0;
			int ret = _client->zrange(key.c_str(), first, last, valueVec, outNum);
			if (ret == 0)
			{
				for (int i = 0; i < outNum; i++)
				{
					if (valueVec[i].str)
					{
						string result = valueVec[i].str;
						values.push_back(result);
					}
					else
					{
						LOG(WARNING) << "redis fail get null";
					}
				}
			}
			return ret;
		}

		//取最前N个，内部可能需要分段取，如果所有的段都是正确的 才返回0
		int ZrangeFirstNElement(string key, int num, vector<string>& values, int step = 200, bool allowError = true)
		{
			store::ss* valueVec;
			double* scoreVec;
			int ret = 0, outNum = 0, finalRet;
			for (int start = 0; start < num; start += step)
			{
				int nowCount = std::min(step, num - start);
				ret = _client->zrange_withscores(key.c_str(), start, start + nowCount - 1, valueVec, scoreVec, outNum);
				if (ret != 0)
				{
					finalRet = ret;
					if (!allowError)
					{
						return ret;
					}
					continue;
				}
				for (int i = 0; i < outNum; i++)
				{
					string value = valueVec[i].str;
					values.push_back(value);
				}
				if (outNum < nowCount)
				{
					break;
				}
			}
			return finalRet;
		}

		vector<string> ZrangeFirstNElement(string key, int num, int step = 200, bool allowError = true)
		{
			vector<string> values;
			store::ss* valueVec;
			double* scoreVec;
			int ret = 0, outNum = 0;
			for (int start = 0; start < num; start += step)
			{
				int nowCount = std::min(step, num - start);
				ret = _client->zrange_withscores(key.c_str(), start, start + nowCount - 1, valueVec, scoreVec, outNum);
				if (ret != 0)
				{
					//LOG(WARING) << "redis fail " << key << " start: " << start << " count: " << start + nowCount - 1;
					if (!allowError)
					{
						return values;
					}
					continue;
				}
				for (int i = 0; i < outNum; i++)
				{
					string value = valueVec[i].str;
					values.push_back(value);
				}
				if (outNum < nowCount)
				{
					break;
				}
			}
			return values;
		}

		template<typename Func>
		int ZrangeFirstNElement(string key, int num, Func func, int step = 200, bool allowError = true)
		{
			store::ss* valueVec;
			double* scoreVec;
			int ret = 0, outNum = 0, finalRet;
			for (int start = 0; start < num; start += step)
			{
				int nowCount = std::min(step, num - start);
				ret = _client->zrange_withscores(key.c_str(), start, start + nowCount - 1, valueVec, scoreVec, outNum);
				if (ret != 0)
				{
					finalRet = ret;
					if (!allowError)
					{
						return ret;
					}
					continue;
				}
				for (int i = 0; i < outNum; i++)
				{
					string value = valueVec[i].str;
					func(value);
				}
				if (outNum < nowCount)
				{
					break;
				}
			}
			return finalRet;
		}

		vector<string> Zrange(string key, int first, int last)
		{
			svec values;
			store::ss* valueVec;
			int outNum;
			int ret = _client->zrange(key.c_str(), first, last, valueVec, outNum);
			if (ret == 0)
			{
				for (int i = 0; i < outNum; i++)
				{
					string value = valueVec[i].str;
					values.push_back(value);
				}
			}
			return values;
		}

		int Get(string key, string& value) const 
		{
			store::ss svalue;
			int ret = _client->get(key.c_str(), svalue);
			if (ret != 0)
			{
				return ret;
			}
			value = svalue.str;
			return ret;
		}

		int count(string key) const
		{
			store::ss svalue;
			return _client->get(key.c_str(), svalue) == 0;
		}

		typedef pair<string, string>* iterator;

		iterator find(const string& key)
		{
			store::ss svalue;
			int ret = _client->get(key.c_str(), svalue);
			if (ret != 0)
			{
				return NULL;
			}
			_item.first = key;
			_item.second = svalue.str;
			return &_item;
		}

		iterator end()
		{
			return NULL;
		}

		string at(const string& key) const
		{
			store::ss svalue;
			int ret = _client->get(key.c_str(), svalue);
			if (ret != 0)
			{
				THROW(key + " not find");
			}
			string value = svalue.str;
			return value;
		}

		string& operator[] (const string& key)
		{
			store::ss svalue;
			int ret = _client->get(key.c_str(), svalue);
			if (ret != 0)
			{
				_item.second = "";
			}
			else
			{
				_item.second = svalue.str;
			}
			return _item.second;
		}

		string operator[] (const string& key) const
		{
			store::ss svalue;
			int ret = _client->get(key.c_str(), svalue);
			if (ret != 0)
			{
				return ""; //@TODO
			}
			string value = svalue.str;
			return value;
		}

	protected:
	private:
		store::RedisClientManager _clientManager;
		store::RedisClient* _client = NULL;
		pair<string, string> _item;
	};

}  //----end of namespace gezi

#endif  //----end of REDIS_CLIENT_H_
