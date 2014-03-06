/**
 *  ==============================================================================
 *
 *          \file   tieba/util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-05 20:48:02.058450
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_UTIL_H_
#define TIEBA_UTIL_H_
#include <string>
#include <boost/algorithm/string.hpp>
namespace gezi {
		inline bool is_thread(std::string title)
		{
			return boost::trim_left_copy(title).find("»Ø¸´£º") != 0;
		}
}  //----end of namespace gezi

#endif  //----end of TIEBA_UTIL_H_
