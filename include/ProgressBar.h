/**
 *  ==============================================================================
 *
 *          \file   ProgressBar.h
 *
 *        \author   gezi
 *
 *          \date   2010-10-13 19:59:53.237718
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef PROGRESS_BAR_H_
#define PROGRESS_BAR_H_
#include <string>
#include <iostream>
#include <iomanip>
#include <boost/progress.hpp>
#include <glog/logging.h>
//#include "common_util.h"
#include "time_util.h" //@TODO  当前使用common_util.h python的封装有问题
using std::string;
namespace gezi {

	class ProgressBar
	{
	public:
		
		ProgressBar() :
			Size(Bar.size() - 1)
		{
		}

		ProgressBar(string log_word) :
			_log_word(log_word), Size(Bar.size() - 1)
		{
		}

		ProgressBar(size_t total) :
			_total(total), Size(Bar.size() - 1)
		{
		}

		ProgressBar(string log_word, size_t total) :
			_log_word(log_word), _total(total), Size(Bar.size() - 1)
		{
		}

		ProgressBar(size_t total, string log_word) :
			_total(total), _log_word(log_word), Size(Bar.size() - 1)
		{
		}
		
		void set_level(int level)
		{
			_level = level;
		}

		size_t counter() const
		{
			return _current;
		}

		void progress(size_t current)
		{
			(*this)(current);
		}
		void progress(size_t current, size_t total)
		{
			(*this)(current, total);
		}
		void operator()(size_t current)
		{
			(*this)(current, _total);
		}

		void operator++()
		{
			(*this)(_current++, _total);
		}

		void operator+=(size_t step)
		{
			(*this)(_current, _total);
			_current += step;
		}

		void operator()(size_t current, size_t total)
		{
			size_t progress = static_cast<int> (100.0 * (current + 1) / total);
			size_t bar_length = static_cast<int> (1.0 * (current + 1) * Size / total);
			if (VLOG_IS_ON(_level) && _prev_progress != progress)
			{
				std::cerr << _log_word << " [ " << current + 1 << " ] (" << _timer.elapsed() << " s)" << std::setw(3) << progress << '%'
					<< " |";
				std::cerr.write(&Bar[0], bar_length);
				std::cerr.write(&Space[0], Size - bar_length);
				std::cerr << '|' << (progress == 100 ? '\n' : '\r');
				//std::cerr << "|\r";
				std::cerr.flush();
				_prev_progress = progress;
			}
		}

	private:
		int _level = 0;
		size_t _prev_progress = 1;
		size_t _current = 0;
		std::string _log_word = "Finished";
		std::string Bar = "*******************************************";
		std::string Space = "                                           ";
		size_t Size;
		size_t _total;
		Timer _timer;
	};

	struct NoProgressBar
	{
		void operator()(size_t, size_t) const
		{
		}
	};
	typedef NoProgressBar DefaultProgressBar;

} //-----------end of gezi

#endif  //----end of PROGRESS_BAR_H_
