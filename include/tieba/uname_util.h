/**
 *  ==============================================================================
 *
 *          \file   tieba/uname_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-20 17:54:42.641428
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_UNAME_UTIL_H_
#define TIEBA_UNAME_UTIL_H_
#include "../common_def.h"
namespace gezi {
	namespace tieba {
		//d数字c中文e英文o其它s开始 @TODO 需要更好的模板表示
		inline string name_pattern(string uname)
		{
			stringstream pattern_stream;
			char pre_pattern = 's';
			for (size_t i = 0; i < uname.size(); i++)
			{
				unsigned high = (unsigned)(0xff & uname[i]);
				if (high >= 0x81)
				{
					if ((high > 0xa9 || high <= 0xa0) && i < uname.size() - 1)
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

		//用户名是否是带有qq联系方式这样的
		inline bool is_qq_name(string uname)
		{
			string normedUname = gezi::normalize_str(uname);
			string qname_pattern = "[[\x81-\xff].q|^q|q[\x81-\xff]|qq|加|扣|店].{0,6}([0-9]){7,30}";
			//PSCONF(qname_pattern, name()); //@FIXME 这个宏如果配置文件里面没有数据的话 速度非常的慢。。。另外可能有多线程问题
			return gezi::reg_find(normedUname, qname_pattern);
		}

		inline bool is_en_num_name(const vector<int>& namePatterns)
		{
			return  vec[0] == 2 && vec.back() == 0;
		}

		inline bool is_en_num_name(string uname)
		{
			vector<int> namePatterns = name_pattern(uname);
			return  vec[0] == 2 && vec.back() == 0;
		}
	} //end of namespace tieba
} //end of namespace gezi

#endif  //----end of TIEBA_UNAME_UTIL_H_
