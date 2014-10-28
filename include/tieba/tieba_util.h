/**
 *  ==============================================================================
 *
 *          \file   tieba_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-09 10:57:27.460545
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_UTIL_H_
#define TIEBA_UTIL_H_

#include "common_util.h"

namespace gezi {
namespace tieba {
	
	inline uint64 reg_span(uint64 nowTime, uint64 regTime)
	{
		uint64 default_regtime = 1071666302; //贴吧大概初始时间

		if (regTime < default_regtime)
		{
			regTime = default_regtime;
		}

		if (nowTime < regTime)
		{
			regTime = nowTime;
		}

		uint64 span = nowTime - regTime; 
		return span;
	}

	//用户当当前位置注册多少天？ 
	inline int reg_days(uint64 nowTime, uint64 regTime)
	{
		uint64 span = reg_span(nowTime, regTime);
		uint64 spanDays = span / kOneDay;
		return spanDays;
	}

	inline bool is_thread(string title)
	{
		return boost::trim_copy(title).find("回复：") != 0;
	}

	inline string get_real_title(string title)
	{
		string title_ = boost::trim_copy(title);
		string mark = "回复：";
		int len = mark.length(); 
		if (title_.find(mark) == 0)
		{
			return boost::trim_left_copy(title_.substr(len));
		}
		else
		{
			return title_;
		}
	}
}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_UTIL_H_
