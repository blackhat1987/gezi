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

namespace gezi
{
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
}

#endif  //----end of TIEBA_UNAME_UTIL_H_
