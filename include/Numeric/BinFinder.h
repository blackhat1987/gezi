/**
 *  ==============================================================================
 *
 *          \file   Numeric/BinFinder.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-04-08 22:25:44.303849
 *
 *  \Description: port from TLC
 *  ==============================================================================
 */

#ifndef NUMERIC__BIN_FINDER_H_
#define NUMERIC__BIN_FINDER_H_

#include "common_def.h"
namespace gezi {

	//@TODO 多次调用会有问题吗 改成static FindBins ? 用类 只是为了省掉 vector重新分配空间的时间？
	/// <summary>
	/// A class that bins an array of Float into a specified number of equal mass bins 
	/// </summary>
	class BinFinder
	{
	private:
		vector<pair<Float, Float> > _binLowerUpperBounds; //first as loewr, second as upper
		vector<pair<int, Float> > _countValues; //first as counts, second as distinct values
	public:

		//@TODO 实现一个Array.Sort(keys[],values[], cmper)
		/// <summary>
		/// Finds the bins.
		/// </summary>
		/// <param name="values">An array if values</param>
		/// <param name="maxBins">The max number of bins to use</param>
		/// <returns>An array of bin upper bounds</returns> @TODO  研究下 是说相似能bin一起？
		Fvec FindBins(Fvec& values, int maxBins)
		{
			// chck whether to allocate datastructures
			size_t sampleSize = values.size();
			size_t allocSize = sampleSize < maxBins ? sampleSize : maxBins;
			if (allocSize > _binLowerUpperBounds.size())
			{
				_binLowerUpperBounds.resize(allocSize, make_pair(0.0, 0.0));
			}
			if (sampleSize > _countValues.size())
			{
				_countValues.resize(sampleSize, make_pair(0, 0.0));
			}
			Fvec result;

			// Get histogram of values
			int numValues = 1;
			std::sort(values.begin(), values.end());
			_countValues[0].second = values[0];
			_countValues[0].first = 1;
			for (int i = 1; i < values.size(); ++i)
			{
				if (values[i] != values[i - 1])
				{
					_countValues[numValues].second = values[i];
					_countValues[numValues].first = 1;
					++numValues;
				}
				else
				{
					_countValues[numValues - 1].first++;
				}
			}

			// case 1: each distinct value is a bin
			if (numValues <= maxBins)
			{
				result.resize(numValues);
				for (int i = 0; i < numValues - 1; ++i)
					result[i] = (_countValues[i].second + _countValues[i + 1].second) / 2;
				result[numValues - 1] = std::numeric_limits<Float>::max();
				return result;
			}

			// case 2: more distinct values than bins

			// find single value bins
			int meanBinSize = _countValues.size() / maxBins;
			sort(_countValues.begin(), _countValues.begin() + numValues, CmpPairByFirstReverse());
			int numBins = 0;
			int countSoFar = 0;
			while (_countValues[numBins].first > meanBinSize)
			{
				_binLowerUpperBounds[numBins].second = _countValues[numBins].second;
				_binLowerUpperBounds[numBins].first = _countValues[numBins].second;
				countSoFar += _countValues[numBins].first;
				++numBins;
			}

			// find remaining bins
			if (numBins < maxBins)
			{
				sort(_countValues.begin() + numBins, _countValues.begin() + numValues, CmpPairBySecond());
				_binLowerUpperBounds[numBins].first = _countValues[numBins].second;
				meanBinSize = (_countValues.size() - countSoFar) / (maxBins - numBins);
				int currBinSize = 0;
				for (int i = numBins; i < numValues - 1; ++i)
				{
					_binLowerUpperBounds[numBins].second = _countValues[i].second;
					currBinSize += _countValues[i].first;
					countSoFar += _countValues[i].first;
					if (currBinSize + _countValues[i + 1].first > meanBinSize)
					{
						++numBins;
						if (numBins == maxBins)
							break;
						_binLowerUpperBounds[numBins].first = _countValues[i + 1].second;
						meanBinSize = (_countValues.size() - countSoFar) / (maxBins - numBins);
						currBinSize = 0;
					}
				}
				if (numBins < maxBins)
				{
					_binLowerUpperBounds[numBins].second = _countValues[numValues - 1].second;
					++numBins;
				}
			}

			// prepare result 
			sort(_binLowerUpperBounds.begin(), _binLowerUpperBounds.begin() + numBins, CmpPairByFirst());
			result.resize(numBins, 0);
			for (int i = 0; i < numBins - 1; ++i)
				result[i] = (_binLowerUpperBounds[i].second + _binLowerUpperBounds[i + 1].first) / 2;
			result[numBins - 1] = std::numeric_limits<Float>::max();
			return result;
		}
	};

}  //----end of namespace gezi

#endif  //----end of NUMERIC__BIN_FINDER_H_
