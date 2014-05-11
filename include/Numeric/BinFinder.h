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
 *                test_binfinder.cc
 *  ==============================================================================
 */

#ifndef NUMERIC__BIN_FINDER_H_
#define NUMERIC__BIN_FINDER_H_

#include "Numeric/find_bins.h"
namespace gezi {

	/// A class that bins an array of Float into a specified number of equal mass bins 
	class BinFinder
	{
	private:
		vector<pair<Float, Float> > _binLowerUpperBounds; //first as lower, second as upper
		vector<pair<int, Float> > _countValues; //first as counts, second as distinct values
	public:
		//注意都会改变values 所以如果需要外部提前备份values
		Fvec FindBins(Fvec& values, int maxBins)
		{
			return find_bins_(values, maxBins, _binLowerUpperBounds, _countValues);
		}

		Fvec FindBins(Fvec& values, int len, int maxBins)
		{
			return find_bins_(values, len, maxBins, _binLowerUpperBounds, _countValues);
		}

		//input -- values, maxBins
		//output-- binUpperBounds, binMedians
		void FindBins(Fvec& values, int maxBins, Fvec& binUpperBounds, Fvec& binMedians)
		{
			find_bins_(values, maxBins, _binLowerUpperBounds, _countValues, binUpperBounds, binMedians);
		}

		void FindBins(Fvec& values, int len, int maxBins, Fvec& binUpperBounds, Fvec& binMedians)
		{
			find_bins_(values, len, maxBins, _binLowerUpperBounds, _countValues, binUpperBounds, binMedians);
		}
	};

}  //----end of namespace gezi

#endif  //----end of NUMERIC__BIN_FINDER_H_
