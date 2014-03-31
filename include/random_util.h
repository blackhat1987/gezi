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
	//注意是闭区间
	typedef std::uniform_int_distribution<uint32_t> RandomRange;

	/*std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(v.begin(), v.end(), g);*/

	inline RandomEngine random_engine(unsigned randSeed = 0, int offset = 0)
	{
		if (randSeed)
		{
			return RandomEngine(randSeed + offset);
		}
		else
		{
			std::random_device rd;
			return RandomEngine(rd());
			//return RandomEngine(random_seed());
		}
	}

	//产生一个[min,max)之间的随机整数
	class RandomInt
	{
	public:
		RandomInt(int max, int min = 0)
			:_d(min, max - 1), _rng(_rd())
		{

		}

		RandomInt(int max, const RandomEngine& rng, int min = 0)
			:_d(min, max - 1), _rng(rng)
		{

		}

		int Next()
		{
			return _d(_rng);
		}
	private:
		std::random_device _rd;
		RandomEngine _rng;
		std::uniform_int_distribution<size_t> _d;
	};

	//genearate 0-1 double number
	class RandomDouble
	{
	public:
		RandomDouble()
			:_d(0.0, 1.0), _rng(_rd())
		{

		}

		RandomDouble(const RandomEngine& rng)
			:_d(0.0, 1.0),_rng(rng)
		{

		}

		int Next()
		{
			return _d(_rng);
		}
	private:
		std::random_device _rd;
		RandomEngine _rng;
		std::uniform_real_distribution<> _d;
	};

	//产生一个[0, max)之间的随机排序 不重复
	class RandomIntRange
	{
	public:
		RandomIntRange(int max, const RandomEngine& rng)
			:_end(max), _rng(rng)
		{
			_vec.resize(max);
			for (int i = 0; i < max; i++) _vec[i] = i;
		}

		int Next()
		{
			std::uniform_int_distribution<size_t> d(0, _end - _index - 1);
			swap(_vec[_index], _vec[_index + d(_rng)]);
			_index++;
			return _vec[_index - 1];
		}
	private:
		int _end;
		int _index = 0;
		ivec _vec;
		RandomEngine _rng;
		std::uniform_int_distribution<size_t> _d;
	};

	template<typename Vec>
	void shuffle(Vec& vec, unsigned randSeed = 0)
	{
		shuffle(vec.begin(), vec.end(), random_engine(randSeed));
	}

	template<typename Vec, typename Rng>
	void shuffle(Vec& vec, const Rng& rng)
	{
		shuffle(vec.begin(), vec.end(), rng);
	}

	template<typename RandomAccessIterator, typename RandomNumberEngine>
	inline void sample(RandomAccessIterator first, RandomAccessIterator last, size_t sample_num, RandomNumberEngine&& rng)
	{
		if (first == last)
			return;

		size_t total = last - first;
		size_t len = std::min(total, sample_num);
		//注意如果len= total 那么最后一个交换其实不需要
		for (size_t i = 0; i < len; i++)
		{
			std::uniform_int_distribution<size_t> d(0, total - i - 1);
			swap(first[i], first[i + d(rng)]);
		}
	}

	template<typename RandomAccessIterator, typename RandomNumberEngine>
	inline void sample_reverse(RandomAccessIterator first, RandomAccessIterator last, size_t sample_num, RandomNumberEngine&& rng)
	{
		if (first == last)
			return;

		typedef typename std::iterator_traits<RandomAccessIterator>::difference_type diff_t;
		diff_t total = last - first;
		diff_t len = std::min(total, (diff_t)sample_num);
		//注意如果len= total 那么最后一个交换其实不需要
		for (diff_t i = total - 1; i >= total - len; i++)
		{
			std::uniform_int_distribution<size_t> d(0, i);
			swap(first[i], first[d(rng)]);
		}
	}

	//just for test
	template<typename RandomAccessIterator, typename RandomNumberEngine>
	inline void shuffle2(RandomAccessIterator first, RandomAccessIterator last, RandomNumberEngine&& rng)
	{
		if (first == last)
			return;

		typedef typename std::iterator_traits<RandomAccessIterator>::difference_type diff_t;
		diff_t n = last - first;
		for (diff_t i = n - 1; i > 0; i--)
		{
			std::uniform_int_distribution<size_t> d(0, i);
			swap(first[i], first[d(rng)]);
		}
	}

	template<typename Vec>
	void sample(Vec& vec, size_t maxNum, unsigned randSeed = 0)
	{
		sample(vec.begin(), vec.end(), maxNum, random_engine(randSeed));
	}

	template<typename Vec, typename Rng>
	void sample(Vec& vec, size_t maxNum, const Rng& rng)
	{
		sample(vec.begin(), vec.end(), maxNum, rng);
	}

	template<typename Vec, typename Rng>
	void sample_reverse(Vec& vec, size_t maxNum, const Rng& rng)
	{
		sample_reverse(vec.begin(), vec.end(), maxNum, rng);
	}
}  //----end of namespace gezi

#endif  //----end of RANDOM_UTIL_H_
