/**
 *  ==============================================================================
 *
 *          \file   tieba/util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-05 20:48:02.058450
 *
 *  \Description:   @TODO move to tieba_util.h
 *  ==============================================================================
 */

#ifndef TIEBA_UTIL_H_
#define TIEBA_UTIL_H_
#include <string>
#include <boost/algorithm/string.hpp>
using std::string;
namespace gezi {
	/*	inline bool is_thread(string title)
		{
			return boost::trim_copy(title).find("»Ø¸´£º") != 0;
		}
		inline string get_real_title(string title)
		{
			string title_ = boost::trim_copy(title);
			string mark = "»Ø¸´£º";
			int len = mark.length();
			if (title_.find(mark) == 0)
			{
				return boost::trim_left_copy(title_.substr(len));
			}
			else
			{
				return title_;
			}
		}*/
}  //----end of namespace gezi

#endif  //----end of TIEBA_UTIL_H_
