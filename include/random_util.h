/**
 *  ==============================================================================
 *
 *          \file   random_util.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-03-30 13:12:25.981986
 *
 *  \Description: gcc4 only
 *  ==============================================================================
 */

#ifndef RANDOM_UTIL_H_
#define RANDOM_UTIL_H_

#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

namespace gezi {
 
	inline unsigned random_seed()
	{
		return std::chrono::system_clock::now().time_since_epoch().count();
	}

	typedef std::default_random_engine RandomEngine;
	typedef RandomEngine Random;
	typedef std::uniform_int_distribution<uint32_t> RandomRange;

	/*std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(v.begin(), v.end(), g);*/

	inline RandomEngine get_random(unsigned randSeed = 0)
	{
		if (randSeed)
		{
			return RandomEngine(randSeed);
		}
		else
		{
			std::random_device rd;
			return RandomEngine(rd());
			//or
			//return RandomEngine(random_seed());
		}
	}

}  //----end of namespace gezi

#endif  //----end of RANDOM_UTIL_H_
