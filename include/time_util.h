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
#include "common_def.h"

using std::string;

namespace gezi {

	inline string get_now_time_str()
	{
		namespace pt = boost::posix_time;
		return pt::to_simple_string(pt::second_clock::local_time());
	}

	inline string to_time_str(uint64 time)
	{
		namespace pt = boost::posix_time;
		using namespace boost::gregorian;
		using namespace boost::posix_time;
		return pt::to_simple_string(from_time_t(time) + hours(8));
	}

	class MicrosecTimer
	{
	public:

		MicrosecTimer() :
			_start_time(boost::posix_time::microsec_clock::local_time())
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
		int _level;

		AutoTimer(string prefix, int level = 2)
			: _prefix(prefix), _level(level)
		{
		}

		~AutoTimer()
		{
			VLOG(_level) << setiosflags(ios::left) << setfill(' ') << setw(40)
				<< _prefix << " " << _timer.elapsed_ms() << " ms";
		}
	};

	class Noticer
	{
	public:
		Noticer(string info, int level = 0, bool caclTime = true)
			:_info(info), _timer(NULL), _level(level)
		{
			VLOG(_level) << _info << " started";
			if (caclTime)
			{
				_timer = new Timer;
			}
		}
		~Noticer()
		{
			if (_timer)
			{
				string prefix = _info + " finished using:";
				VLOG(_level) << setiosflags(ios::left) << setfill(' ') << setw(40)
					<< prefix << " " << "[" << _timer->elapsed_ms() << " ms] "
					<< "(" << _timer->elapsed() << " s)";
			}
			else
			{
				VLOG(_level) << _info << " finished";
			}

			FREE(_timer);
		}
	private:
		string _info;
		Timer* _timer;
		int _level;
	};

	class Notifer
	{
	public:
		Notifer(string info, int level = 0)
			:_info(info), _level(level)
		{
		}
		~Notifer()
		{
			string prefix = _info + " using:";
			VLOG(_level) << setiosflags(ios::left) << setfill(' ') << setw(40)
				<< prefix << " " << "[" << _timer.elapsed_ms() << " ms] "
				<< "(" << _timer.elapsed() << " s)";
		}
	private:
		string _info;
		Timer _timer;
		int _level;
	};
} //----end of namespace gezi

#endif  //----end of TIME_UTIL_H_
