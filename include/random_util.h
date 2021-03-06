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

#if __GNUC__ > 3
#include <random>       // std::default_random_engine
//#include <chrono>       // std::chrono::system_clock
#else //for python wrapper most since gccxml does not support gcc4
#include <boost/random.hpp>
//#include <boost/chrono.hpp>
namespace std {
	using boost::random::uniform_int_distribution;
	using boost::random::uniform_real_distribution;
	typedef boost::random::mt19937 default_random_engine;
	//using boost::chrono::system_clock;
}
#endif
#include "common_def.h"
namespace gezi {

	inline unsigned random_seed()
	{
		//#include <chrono>       // std::chrono::system_clock
		//return std::chrono::system_clock::now().time_since_epoch().count();
		return std::random_device()();
	}

	typedef std::default_random_engine RandomEngine;
	//注意是闭区间
	typedef std::uniform_int_distribution<uint32_t> UintDistribution;

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
			return RandomEngine(std::random_device()());
		}
	}

	//产生一个[min,max)之间的随机整数
	class RandomInt
	{
	public:
		RandomInt(int max, int min = 0)
			:_d(min, max - 1), _rng(random_seed())
		{

		}

		RandomInt(int max, const RandomEngine& rng, int min = 0)
			:_d(min, max - 1), _rng(rng)
		{

		}

		int Next() const
		{
			return _d(_rng);
		}
	private:
		std::uniform_int_distribution<size_t> _d;
		RandomEngine _rng;
	};

	//genearate 0-1 double number
	class RandomDouble
	{
	public:
		RandomDouble(double lower = 0.0, double upper = 1.0)
			:_d(lower, upper), _rng(random_seed())
		{

		}

		RandomDouble(const RandomEngine& rng, double lower = 0.0, double upper = 1.0)
			:_d(lower, upper), _rng(rng)
		{

		}

		double Next() const
		{
			return _d(_rng);
		}
	private:
		std::uniform_real_distribution<> _d;
		RandomEngine _rng;
	};

	//模仿c#
	class Random
	{
	public:
		Random()
			:_rng(random_seed())
		{
		}
		
		Random(unsigned seed)
			:_rng(seed)
		{

		}

		Random(const RandomEngine& rng)
			:_rng(rng)
		{

		}

		void seed(unsigned seed_)
		{
			_rng.seed(seed_);
		}

		//return int in [0, max int)
		int Next() const 
		{
			std::uniform_int_distribution<int> d(0, std::numeric_limits<int>::max());
			return d(_rng);
		}

		//return int in[0, max)
		int Next(int max) const 
		{
			std::uniform_int_distribution<int> d(0, max - 1);
			return d(_rng);
		}
		
		//return int in [min,max)
		int Next(int min, int max) const 
		{
			std::uniform_int_distribution<int> d(min, max - 1);
			return d(_rng);
		}

		//return double in [0.0,1.0]
		double NextDouble() const 
		{
			std::uniform_real_distribution<> d;
			return d(_rng);
		}

		Float NextFloat() const
		{
			std::uniform_real_distribution<> d;
			return d(_rng);
		}
	private:
		RandomEngine _rng;
	};

	typedef shared_ptr<Random> RandomPtr;

	//产生一个[0, max)之间的随机排序 不重复 
	//单线程。。。

	class RandomRange
	{
	public:
		RandomRange(int max)
			:_end(max), _rng(random_seed())
		{
			Init();
		}

		RandomRange(int max, const RandomEngine& rng)
			:_end(max), _rng(rng)
		{
			Init();
		}

		int Next() 
		{
			std::uniform_int_distribution<size_t> d(0, _end - _index - 1);
			swap(_vec[_index], _vec[_index + d(_rng)]);
			int index = _index;
			_index = (_index + 1) % _end;
			//Pvec(_vec);
			return _vec[index];
		}
	private:
		void Init()
		{
			_vec.resize(_end);
			for (int i = 0; i < _end; i++)
				_vec[i] = i;
		}
	private:
		ivec _vec;
		int _end;
		int _index = 0;
		RandomEngine _rng;
	};

	typedef shared_ptr<RandomRange> RandomRangePtr;

	template<typename Vec>
	void shuffle(Vec& vec, unsigned randSeed = 0)
	{
		shuffle(vec.begin(), vec.end(), random_engine(randSeed));
	}

#ifndef GCCXML  //@TODO GCC3不支持move语义 暂时脚本也不支持&&转成& 以及 处理方式是&&直接去掉 这种对class内部&& 构造暂时ok 但是对于普通函数的&&需要不同的处理 目前看最好是转成& 失掉临时变量的灵活性

	//@FIXME 为什么不去优先匹配上面的 却匹配下面的模板报错了呢。。shuffle(vec, FLAGS_seed); ???
	//是比较严格 需要 shuffle(vec, (unsigned)FLAGS_seed);
	template<typename Vec, typename Rng>
	void shuffle(Vec& vec, Rng&& rng)
	{
		shuffle(vec.begin(), vec.end(), rng);
	}

	/*template<typename Vec>
	void shuffle(Vec& vec, const RandomEngine& rng)
	{
	shuffle(vec.begin(), vec.end(), rng);
	}*/

	template<typename RandomAccessIterator, typename RandomNumberEngine>
	void sample(RandomAccessIterator first, RandomAccessIterator last, size_t sample_num, RandomNumberEngine&& rng)
	{
		if (first == last)
			return;

		size_t total = last - first;
		size_t len = std::min(total, sample_num);
		//注意如果len= total 那么最后一个交换其实不需要
		for (size_t i = 0; i < len; i++)
		{
			swap(first[i], first[i + d(rng)]);
			std::uniform_int_distribution<size_t> d(0, total - i - 1);
		}
	}

	template<typename RandomAccessIterator, typename RandomNumberEngine>
	void sample_reverse(RandomAccessIterator first, RandomAccessIterator last, size_t sample_num, RandomNumberEngine&& rng)
	{
		if (first == last)
			return;

		typedef typename std::iterator_traits<RandomAccessIterator>::difference_type diff_t;
		diff_t total = last - first;
		diff_t len = std::min(total, (diff_t)sample_num);
		//注意如果len= total 那么最后一个交换其实不需要
		for (diff_t i = total - 1; i >= total - len; i--)
		{
			std::uniform_int_distribution<size_t> d(0, i);
			swap(first[i], first[d(rng)]);
		}
	}

	//just for test
	template<typename RandomAccessIterator, typename RandomNumberEngine>
	void shuffle2(RandomAccessIterator first, RandomAccessIterator last, RandomNumberEngine&& rng)
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
	void sample(Vec& vec, size_t maxNum, Rng&& rng)
	{
		sample(vec.begin(), vec.end(), maxNum, rng);
	}

	/*template<typename Vec>
	void sample(Vec& vec, size_t maxNum, const RandomEngine& rng)
	{
	sample(vec.begin(), vec.end(), maxNum, rng);
	}*/

	template<typename Vec, typename Rng>
	void sample_reverse(Vec& vec, size_t maxNum, Rng&& rng)
	{
		sample_reverse(vec.begin(), vec.end(), maxNum, rng);
	}

	//数组中找到最大的位置，只是有fraction的比例的数据被忽略，如果万一实际都被忽略 那么还是选最大的位置
	template<typename Vec>
	int max_pos_rand(const Vec& vec, Random& rand, double fraction)
	{
		if (vec.empty())
		{
			return -1;
		}
		typedef typename Vec::value_type T;
		T maxVal = vec[0];
		int maxPos = 0;
		T maxVal2 = vec[0];
		int maxPos2 = 0;
		bool findOne = false;
		for (int i = 0; i < (int)vec.size(); i++)
		{
			if (maxVal < vec[i])
			{
				maxVal = vec[i];
				maxPos = i;
			}

			if (rand.NextDouble() > fraction)
			{
				if (findOne == false || maxVal2 < vec[i])
				{
					maxVal2 = vec[i];
					maxPos2 = i;
				}
				findOne = true;
			}
		}
		if (findOne)
		{
			return maxPos2;
		}
		else
		{
			return maxPos;
		}
	}

	template<typename Vec, typename CmpFunc>
	int max_pos_rand(const Vec& vec, Random& rand, double fraction, CmpFunc cmp)
	{
		if (vec.empty())
		{
			return -1;
		}
		typedef typename Vec::value_type T;
		T maxVal = vec[0];
		int maxPos = 0;
		T maxVal2 = vec[0];
		int maxPos2 = 0;
		bool findOne = false;
		for (int i = 0; i < (int)vec.size(); i++)
		{
			if (cmp(maxVal, vec[i]))
			{
				maxVal = vec[i];
				maxPos = i;
			}

			if (rand.NextDouble() > fraction)
			{
				if (findOne == false || cmp(maxVal2, vec[i]))
				{
					maxVal2 = vec[i];
					maxPos2 = i;
				}
				findOne = true;
			}
		}
		if (findOne)
		{
			return maxPos2;
		}
		else
		{
			return maxPos;
		}
	}
	//template<typename Vec>
	//void sample_reverse(Vec& vec, size_t maxNum, const RandomEngine& rng)
	//{
	//	sample_reverse(vec.begin(), vec.end(), maxNum, rng);
	//}
#endif //GCCXML
}  //----end of namespace gezi

#endif  //----end of RANDOM_UTIL_H_
