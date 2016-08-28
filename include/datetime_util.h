/**
 *  ==============================================================================
 *
 *          \file   datetime_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-12-18 13:55:58.005378
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef DATETIME_UTIL_H_
#define DATETIME_UTIL_H_
//date time @FIXMEºÍpy++ gccxml³åÍ»
#include <boost/date_time/posix_time/posix_time.hpp>

#include "common_util.h"

#ifndef GCCXML
using namespace boost::gregorian;
using namespace boost::posix_time;
#endif

namespace gezi
{

	inline int get_hour(int64 timestamp)
	{
		ptime pt = from_time_t(timestamp);
		tm t = to_tm(pt);
		return t.tm_hour + 8;
	}

	inline int64 now_time()
	{
		return time(NULL);
	}

	static const int kOneDay = 86400; //24 * 60 * 60
	static const int kOneHour = 3600;
	static const int kOneMinute = 60;
}

#endif  //----end of DATETIME_UTIL_H_
