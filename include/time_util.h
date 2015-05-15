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
			return d.ticks() / (double)d.ticks_per_second();
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

#ifndef GCCXML
#include "datetime_util.h" //和gccxml冲突
	template<typename _Key,
		template<class _Kty, class _Ty, typename...> class _Map = std::unordered_map>
	class TimerMap
	{
	public:
		typedef _Key Key;
		typedef _Map<Key, int64> Map;
		typedef typename Map::iterator iterator;
		typedef typename Map::const_iterator const_iterator;
	public:
		TimerMap()
		{

		}

		TimerMap(int64 span)
			:_span(span)
		{

		}

		//普通map不支持设定大小 LruMap才支持设置最大容量
		TimerMap(int capacity)
		{
			_map.set_capacity(capacity);
		}

		TimerMap(int64 span, int capacity)
			:_span(span)
		{
			_map.set_capacity(capacity);
		}

		void set_capacity(int capacity)
		{
			_map.set_capacity(capacity);
		}

		void SetCapacity(int capacity)
		{
			_map.set_capacity(capacity);
		}

		void SetSpan(int span)
		{
			_span = span;
		}

		//open mp环境下线程安全保证，其它条件不保证线程安全
		bool count(const Key& key)
		{
			//注意这里多线程可能会core因为 
			//iterator find(const key_type& k); //这个应该不是线程安全的,
			//const_iterator find(const key_type& k) const; 
			//It should be fine.You can use const references to it if you want to document / enforce read - only behaviour.
			//	Note that correctness isn't guaranteed (in principle the map could choose to rebalance itself on a call to find), even if you do use const methods only (a really perverse implementation could declare the tree mutable). However, this seems pretty unlikely in practise.
			//const_iterator iter = _map.find(key);
			//auto iter = _map.find(key) //如果机上critical 会显示error: 'iter' was not declared in this scope 下面
			iterator iter;
#pragma omp critical
			{
				iter = _map.find(key);
			}
			int64 nowTime = now_time();

			if (iter == _map.end())
			{
#pragma  omp critical
				{
					_map[key] = nowTime;
				}
				return false;
			}
			else
			{
				int64 oldTime = iter->second;
				if (nowTime - oldTime >= _span)
				{
#pragma  omp critical
					{
						iter->second = nowTime;
					}
					return false;
				}
				else
				{
					return true;
				}
			}
		}

	private:
		Map _map;
		int64 _span;
	};
#endif //GCCXML
} //----end of namespace gezi

#endif  //----end of TIME_UTIL_H_
