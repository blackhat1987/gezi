/**
 *  ==============================================================================
 *
 *          \file   time_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-17 16:41:41.824662
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIME_UTIL_H_
#define TIME_UTIL_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/progress.hpp>
#include <glog/logging.h>
#include <string>
using std::string;
namespace gezi
{
	class MicrosecTimer
	{
	public:

		MicrosecTimer() : _start_time(boost::posix_time::microsec_clock::local_time())
		{
		}

		~MicrosecTimer()
		{
		}

		void restart()
		{
			_start_time = boost::posix_time::microsec_clock::local_time();
		}

		double elapsed()
		{
			boost::posix_time::time_duration d = boost::posix_time::microsec_clock::local_time() - _start_time;
			double result = d.ticks();
			return result /= d.ticks_per_second();
		}

		double elapsed_ms()
		{
			return elapsed() * 1000.0;
		}

	private:
		boost::posix_time::ptime _start_time;
	};

	typedef MicrosecTimer Timer;

	class AutoTimer
	{
	public:
		string _prefix;
		MicrosecTimer _timer;

		AutoTimer(const string& prefix)
			: _prefix(prefix)
		{
		}

		~AutoTimer()
		{
			VLOG(2) << setiosflags(ios::left) << setfill(' ') << setw(40)
				<< _prefix << " " << _timer.elapsed_ms() << " ms";
		}
	};
} //----end of namespace gezi

#endif  //----end of TIME_UTIL_H_
