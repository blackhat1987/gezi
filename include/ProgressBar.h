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

namespace gezi {
	class ProgressBar
	{
	public:

		ProgressBar() :
			Size(Bar.size() - 1)
		{
		}

		ProgressBar(const std::string& log_word) :
			_log_word(log_word), 
			Size(Bar.size() - 1)
		{
		}


		ProgressBar(size_t total) :
			_total(total), 
			Size(Bar.size() - 1)
		{
		}

		ProgressBar(const std::string& log_word, size_t total) :
			_log_word(log_word), _total(total), 
			Size(Bar.size() - 1)
		{
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
		void operator()(size_t current, size_t total)
		{
			size_t progress = static_cast<int> (100.0 * (current + 1) / total);
			size_t bar_length = static_cast<int> (1.0 * (current + 1) * Size / total);
			if (_prev_progress != progress)
			{
				std::cout << _log_word << " [ " << current + 1 << " ] (" << _timer.elapsed() << " s)" << std::setw(3) << progress << '%'
					<< " |";
				std::cout.write(&Bar[0], bar_length);
				std::cout.write(&Space[0], Size - bar_length);
				std::cout << '|' << (progress == 100 ? '\n' : '\r');
				std::cout.flush();
				_prev_progress = progress;
			}
		}

	private:
		size_t _prev_progress = 1;
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

}

#endif  //----end of PROGRESS_BAR_H_
