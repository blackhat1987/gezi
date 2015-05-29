/**
 *  ==============================================================================
 *
 *          \file   Numeric/find_bins.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-05-07 17:00:53.089639
 *
 *  \Description:  test_binfinder.cc
 *  ==============================================================================
 */

#ifndef NUMERIC_FIND_BINS_H_
#define NUMERIC_FIND_BINS_H_
#include "common_def.h"
#include "common_util.h"
namespace gezi {

	//输入的countValues是resize之后的
	inline int find_distinct_counts(Fvec& values, vector<pair<int, Float> >& countValues)
	{
		int numDistinctValues = 1;

		if (!values.empty())
		{ //兼容边界条件 value是空的时候 返回1个bin max最大值，median设置为0
			sort(values.begin(), values.end());

			countValues[0].first = 1;
			countValues[0].second = values[0];

			for (size_t i = 1; i < values.size(); i++)
			{
				if (values[i] != values[i - 1])
				{
					countValues[numDistinctValues].first = 1;
					countValues[numDistinctValues].second = values[i];
					numDistinctValues++;
				}
				else
				{
					countValues[numDistinctValues - 1].first++;
				}
			}
		}

		return numDistinctValues;
	}

	//输入是一个近似稀疏表示,所有非0元素排列(values), 整个完整序列长度, 注意输入需要确保values里面没有0
	inline int find_distinct_counts(Fvec& values, int len, vector<pair<int, Float> >& countValues)
	{
		int numDistinctValues = find_distinct_counts(values, countValues);
		int numZeros = len - values.size();
		if (numZeros <= 0) //注意伪稀疏特殊直接返回
			return numDistinctValues;

		if (values.empty())
		{
			countValues[0].first = len;
			countValues[0].second = 0.0;
			return 1;
		}
		else
		{
			auto item = make_pair(numZeros, (Float)0.0); //auto item = make_pair(numZeros, 0.0); item.second会默认double类型
			//注意不是countValues.end()因为空间复用
			auto iter = std::lower_bound(countValues.begin(), countValues.begin() + numDistinctValues, item, CmpPairBySecond());
			countValues.insert(iter, item); //@TODO insert ?
			return numDistinctValues + 1;
		}
	}

	//存在问题 1,2,2,2,2,3分成2个桶 会出错,2独占一桶是不对的
	//找binUpperBound的核心代码 返回binUpperBound
	inline Fvec find_bins(vector<pair<int, Float> >& countValues,
		vector<pair<Float, Float> >& binLowerUpperBounds,
		int maxBins, int sampleSize, int numDistinctValues)
	{
		Fvec result;
		// case 1: each distinct value is a bin
		if (numDistinctValues <= maxBins)
		{
			result.resize(numDistinctValues);
			for (int i = 0; i < numDistinctValues - 1; ++i)
				result[i] = (countValues[i].second + countValues[i + 1].second) / 2;
			result[numDistinctValues - 1] = std::numeric_limits<Float>::max();
			return result;
		}

		// case 2: more distinct values than bins
		// find single value bins
		int meanBinSize = sampleSize / maxBins;
		sort(countValues.begin(), countValues.begin() + numDistinctValues, CmpPairByFirstReverse());
		int numBins = 0;
		int countSoFar = 0;
		while (countValues[numBins].first > meanBinSize)
		{
			binLowerUpperBounds[numBins].second = countValues[numBins].second;
			binLowerUpperBounds[numBins].first = countValues[numBins].second;
			countSoFar += countValues[numBins].first;
			++numBins;
		}

		// find remaining bins
		if (numBins < maxBins)
		{
			sort(countValues.begin() + numBins, countValues.begin() + numDistinctValues, CmpPairBySecond());
			binLowerUpperBounds[numBins].first = countValues[numBins].second;
			meanBinSize = (sampleSize - countSoFar) / (maxBins - numBins);
			int currBinSize = 0;
			for (int i = numBins; i < numDistinctValues - 1; ++i)
			{
				binLowerUpperBounds[numBins].second = countValues[i].second;
				currBinSize += countValues[i].first;
				countSoFar += countValues[i].first;
				if (currBinSize + countValues[i + 1].first > meanBinSize)
				{
					++numBins;
					if (numBins == maxBins)
						break;
					binLowerUpperBounds[numBins].first = countValues[i + 1].second;
					meanBinSize = (sampleSize - countSoFar) / (maxBins - numBins);
					currBinSize = 0;
				}
			}
			if (numBins < maxBins)
			{
				binLowerUpperBounds[numBins].second = countValues[numDistinctValues - 1].second;
				++numBins;
			}
		}
		// prepare result 
		sort(binLowerUpperBounds.begin(), binLowerUpperBounds.begin() + numBins, CmpPairByFirst());
		//fix tlc的这个问题 bug
		//$10 = (__gnu_cxx::__alloc_traits<std::allocator<std::pair<double, double> > >::value_type &) @0xcafef70: {first = 19761, second = 19761}
		//(gdb)p binLowerUpperBounds[248]
		//	$11 = (__gnu_cxx::__alloc_traits<std::allocator<std::pair<double, double> > >::value_type &) @0xcafef80: {first = 20125, second = 32685}
		//(gdb)p binLowerUpperBounds[249]
		//	$12 = (__gnu_cxx::__alloc_traits<std::allocator<std::pair<double, double> > >::value_type &) @0xcafef90: {first = 20733, second = 20733}
		//(gdb)p binLowerUpperBounds[250]
		//	$14 = (__gnu_cxx::__alloc_traits<std::allocator<std::pair<double, double> > >::value_type &) @0xcafefa0: {first = 21533, second = 21533}
		for (int i = 0; i < numBins - 1; i++)
		{
			if (binLowerUpperBounds[i].second > binLowerUpperBounds[i + 1].second)
			{
				std::swap(binLowerUpperBounds[i].second, binLowerUpperBounds[i + 1].second);
			}
		}
		result.resize(numBins, 0);
		for (int i = 0; i < numBins - 1; ++i)
			result[i] = (binLowerUpperBounds[i].second + binLowerUpperBounds[i + 1].first) / 2;
		result[numBins - 1] = std::numeric_limits<Float>::max();
		return result;
	}

	//@TODO 实现一个Array.Sort(keys[],values[], cmper) 用类更方便？
	inline Fvec find_bins_(Fvec& values, int maxBins,
		vector<pair<Float, Float> >& binLowerUpperBounds,
		vector<pair<int, Float> >& countValues)
	{
		// check whether to allocate datastructures
		int sampleSize = values.size();
		int allocSize = sampleSize < maxBins ? sampleSize : maxBins;

		if (allocSize > (int)binLowerUpperBounds.size())
		{
			binLowerUpperBounds.resize(allocSize, make_pair(0.0, 0.0));
		}
		if (sampleSize > (int)countValues.size())
		{
			countValues.resize(sampleSize, make_pair(0, 0.0));
		}

		// Get histogram of values
		int numValues = find_distinct_counts(values, countValues);

		return find_bins(countValues, binLowerUpperBounds, maxBins, sampleSize, numValues);
	}

	inline Fvec find_bins_(Fvec& values, int len, int maxBins,
		vector<pair<Float, Float> >& binLowerUpperBounds,
		vector<pair<int, Float> >& countValues)
	{
		// check whether to allocate datastructures
		int sampleSize = len;
		int allocSize = sampleSize < maxBins ? sampleSize : maxBins;

		if ((size_t)allocSize > binLowerUpperBounds.size())
		{
			binLowerUpperBounds.resize(allocSize, make_pair(0.0, 0.0));
		}
		if ((size_t)sampleSize > countValues.size())
		{
			countValues.resize(sampleSize, make_pair(0, 0.0));
		}

		// Get histogram of values
		int numValues = find_distinct_counts(values, len, countValues);

		return find_bins(countValues, binLowerUpperBounds, maxBins, sampleSize, numValues);
	}

	inline void find_medians(vector<pair<int, Float> >& countValues,
		int numValues, int maxBins,
		Fvec& binUpperBounds, Fvec& binMedians)
	{
		if (numValues <= maxBins)
		{
			if (countValues.empty())
			{
				binMedians.push_back(0);
			}
			else
			{
				for (int i = 0; i < numValues; i++)
				{
					binMedians.push_back(countValues[i].second);
				}
			}
		}
		else
		{
			sort(countValues.begin(), countValues.begin() + numValues, CmpPairBySecond());
			binMedians.resize(maxBins);
			int bin = 0;
			int countInBin = 0;
			for (int v = 0; v < numValues; v++)
			{ //小数组可能会有误差  目前保持和TLC一致
				if (countValues[v].second > binUpperBounds[bin])
				{
					int medianCount = countInBin / 2;
					int partialCount = 0;
					int v2 = v;
					while (partialCount < medianCount)
					{
						partialCount += countValues[--v2].first;
					}
					binMedians[bin] = countValues[v2].second;
					countInBin = 0;
					bin++;
				}
				countInBin += countValues[v].first;
			}
			int medianCount = countInBin / 2;
			int partialCount = 0;
			int v2 = numValues;
			while (partialCount < medianCount)
			{
				partialCount += countValues[--v2].first;
			}
			binMedians[bin] = countValues[v2].second;
		}
	}

	//find binUpperBounds and binMedians
	inline void find_bins_(Fvec& values, int maxBins,
		vector<pair<Float, Float> >& binLowerUpperBounds,
		vector<pair<int, Float> >& countValues,
		Fvec& binUpperBounds, Fvec& binMedians)
	{
		// check whether to allocate datastructures
		int sampleSize = values.size();
		int allocSize = sampleSize < maxBins ? sampleSize : maxBins;

		if (allocSize > (int)binLowerUpperBounds.size())
		{
			binLowerUpperBounds.resize(allocSize, make_pair(0.0, 0.0));
		}
		if (sampleSize > (int)countValues.size())
		{
			countValues.resize(sampleSize, make_pair(0, 0.0));
		}

		// Get histogram of values
		int numValues = find_distinct_counts(values, countValues);
		binUpperBounds = find_bins(countValues, binLowerUpperBounds, maxBins, sampleSize, numValues);
		find_medians(countValues, numValues, maxBins, binUpperBounds, binMedians);
	}

	inline void find_bins_(Fvec& values, int len, int maxBins,
		vector<pair<Float, Float> >& binLowerUpperBounds,
		vector<pair<int, Float> >& countValues,
		Fvec& binUpperBounds, Fvec& binMedians)
	{
		// check whether to allocate datastructures
		int sampleSize = len;
		int allocSize = sampleSize < maxBins ? sampleSize : maxBins;

		if (allocSize > (int)binLowerUpperBounds.size())
		{
			binLowerUpperBounds.resize(allocSize, make_pair(0.0, 0.0));
		}
		if (sampleSize > (int)countValues.size())
		{
			countValues.resize(sampleSize, make_pair(0, 0.0)); //注意这个可能coutValues.size > sampleSize!
		}

		// Get histogram of values
		int numValues = find_distinct_counts(values, len, countValues);
		binUpperBounds = find_bins(countValues, binLowerUpperBounds, maxBins, sampleSize, numValues);
		find_medians(countValues, numValues, maxBins, binUpperBounds, binMedians);
	}

	//输入是dense表示的数组 例如[0,0,0,3,2.3,4.5,4.3,4.5]
	//输出bin分割点向量 
	inline Fvec find_bins(Fvec& values, int maxBins)
	{
		vector<pair<Float, Float> > binLowerUpperBounds; //first as lower, second as upper
		vector<pair<int, Float> > countValues; //first as counts, second as distinct values
		return find_bins_(values, maxBins, binLowerUpperBounds, countValues);
	}

	inline Fvec find_bins(Fvec& values, int len, int maxBins)
	{
		vector<pair<Float, Float> > binLowerUpperBounds; //first as lower, second as upper
		vector<pair<int, Float> > countValues; //first as counts, second as distinct values
		return find_bins_(values, len, maxBins, binLowerUpperBounds, countValues);
	}

	//find binUpperBounds and binMedians
	inline void find_bins(Fvec& values, int maxBins, Fvec& binUpperBounds, Fvec& binMedians)
	{
		vector<pair<Float, Float> > binLowerUpperBounds; //first as lower, second as upper
		vector<pair<int, Float> > countValues; //first as counts, second as distinct values
		find_bins_(values, maxBins, binLowerUpperBounds, countValues, binUpperBounds, binMedians);
	}


	inline void find_bins(Fvec& values, int len, int maxBins, Fvec& binUpperBounds, Fvec& binMedians)
	{
		vector<pair<Float, Float> > binLowerUpperBounds; //first as lower, second as upper
		vector<pair<int, Float> > countValues; //first as counts, second as distinct values
		find_bins_(values, len, maxBins, binLowerUpperBounds, countValues, binUpperBounds, binMedians);
	}

}  //----end of namespace gezi

#endif  //----end of NUMERIC_FIND_BINS_H_
