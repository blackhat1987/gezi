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
class ProgressBar
{
public:

    ProgressBar() : 
			prev_progress_(0),
			log_word_("Finished:"), 
			Bar("*******************************************"), 
			Space("                                           "), 
			Size(Bar.size() - 1)
    {
    }

    ProgressBar(const std::string& log_word) : 
			prev_progress_(0), 
			log_word_(log_word), 
			Bar("*******************************************"), 
			Space("                                           "), 
			Size(Bar.size() - 1)
    {
    }


		ProgressBar(size_t total) : 
			prev_progress_(0), 
			log_word_("FinishedT_T"),
			Bar("*******************************************"),
			Space("                                           "), 
			Size(Bar.size() - 1), 
			total_(total)
		{
		}

		ProgressBar(const std::string& log_word, size_t total) :
			prev_progress_(0),
			log_word_(log_word),
			Bar("*******************************************"),
			Space("                                           "),
			Size(Bar.size() - 1),
			total_(total)
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
			(*this)(current, total_);
		}
    void operator()(size_t current, size_t total)
    {
        size_t progress = static_cast<int> (100.0 * (current + 1) / total);
        size_t bar_length = static_cast<int> (1.0 * (current + 1) * Size / total);

        if (prev_progress_ != progress)
        {
            std::cout << log_word_ << " |" << std::setw(3) << progress << '%'
                    << " |";
            std::cout.write(&Bar[0], bar_length);
            std::cout.write(&Space[0], Size - bar_length);
            std::cout << '|' << (progress == 100 ? '\n' : '\r');
            prev_progress_ = progress;
        }
    }

private:
    size_t prev_progress_;
    std::string log_word_;
    std::string Bar;
    std::string Space;
    size_t Size;
		size_t total_;
};

struct NoProgressBar
{

    void operator()(size_t, size_t) const
    {
    }
};

typedef NoProgressBar DefaultProgressBar;
#endif  //----end of PROGRESS_BAR_H_
