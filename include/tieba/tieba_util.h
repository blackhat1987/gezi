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
	
	//用户当当前位置注册多少天？ 
	inline int reg_days(uint64 nowTime, uint64 regTime)
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
		uint64 spanDays = span / kOneDay;
		return spanDays;
	}

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_UTIL_H_
