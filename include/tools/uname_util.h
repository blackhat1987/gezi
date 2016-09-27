/**
 *  ==============================================================================
 *
 *          \file   tools/uname_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-20 17:54:42.641428
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TOOLS_UNAME_UTIL_H_
#define TOOLS_UNAME_UTIL_H_
#include "common_util.h"
namespace gezi {
	//d数字c中文e英文o其它s开始 @TODO 需要更好的模板表示
	//0    1   2    3
	inline string name_pattern(string uname)
	{
		if (uname.empty())
		{
			return "o";
		}

		stringstream pattern_stream;
		char pre_pattern = 's';
		for (size_t i = 0; i < uname.size(); i++)
		{
			unsigned high = (unsigned)(0xff & uname[i]);
			if (high >= 0x81)
			{
				if ((high > 0xa9 || high <= 0xa0) && i < uname.size() - 1)
				{
					if (is_gbk_ch(uname[i], uname[i + 1]))
					{
						if (pre_pattern != 'c')
						{
							pre_pattern = 'c';
							pattern_stream << "c";
						}
					}
					else
					{
						if (pre_pattern != 'o')
						{
							pre_pattern = 'o';
							pattern_stream << "o";
						}
					}
				}
				else
				{
					if (pre_pattern != 'o')
					{
						pre_pattern = 'o';
						pattern_stream << "o";
					}
				}
				i++;
			}
			else
			{
				if (uname[i] >= 'a' && uname[i] <= 'z' || uname[i] >= 'A' && uname[i] <= 'Z')
				{
					if (pre_pattern != 'e')
					{
						pre_pattern = 'e';
						pattern_stream << "e";
					}
				}
				else if (uname[i] >= '0' && uname[i] <= '9')
				{
					if (pre_pattern != 'd')
					{
						pre_pattern = 'd';
						pattern_stream << "d";
					}
				}
				else
				{
					if (pre_pattern != 'o')
					{
						pre_pattern = 'o';
						pattern_stream << "o";
					}
				}
			}
		}
		return pattern_stream.str();
	}


	//获取用户名的3位表示
	inline string simple_name_pattern(string uname)
	{
		char pattern[4] = { 0 };
		string np = name_pattern(uname);
		pattern[0] = np[0];
		pattern[2] = np.back(); //c++11 only
		if (np.size() < 3)
		{
			pattern[1] = np.back();
		}
		else
		{
			pattern[1] = np[1];
			for (size_t i = 1; i < np.size() - 1; i++)
			{
				if (np[i] != np[0] && np[i] != np.back())
				{
					pattern[1] = np[i];
					break;
				}
			}
		}
		return pattern;
	}

	inline vector<int> name_feature(string uname)
	{
		string template_ = "dceo";
		vector<int> vec;
		string pattern = simple_name_pattern(uname);
		foreach(char c, pattern)
		{
			vec.push_back(template_.find(c));
		}
		return vec;
	}

	//用户名是否是带有qq联系方式这样的
	inline bool is_qq_name(string uname)
	{
		string normedUname = gezi::normalize_str(uname);
		string qname_pattern = "[[\x81-\xff].q|^q|q[\x81-\xff]|qq|加|扣|店].{0,6}([0-9]){7,30}";
		//PSCONF(qname_pattern, name()); //@FIXME 这个宏如果配置文件里面没有数据的话 速度非常的慢。。。另外可能有多线程问题
		return gezi::reg_find(normedUname, qname_pattern);
	}

	inline bool is_en_num_name(const vector<int>& nameFeatures)
	{
		return  nameFeatures[0] == 2 && nameFeatures.back() == 0;
	}

	inline bool is_en_num_name(string uname)
	{
		return name_pattern(uname) == "ed";
	}

	inline bool is_en_num_simple_name_pattern(string pattern)
	{
		return pattern == "edd";
	}
} //end of namespace gezi

#endif  //----end of TOOLS_UNAME_UTIL_H_
