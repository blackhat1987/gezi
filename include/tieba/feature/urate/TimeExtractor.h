/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/TimeExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-14 06:19:22.947043
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__TIME_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__TIME_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
namespace tieba {

class TimeExtractor : public UrateExtractor
{
public:
	TimeExtractor(string name = "Time")
		:UrateExtractor(name)
	{

	}

	//用户当前发帖时间 落在桶的位置  1点之后 嫌疑大 1-5 5-9 9-13 13-17 17-21 21-1
	//用户帖子的桶分布 也有意义 大量在 1-5发 嫌疑大
	static void extract_bins(const vector<int64>& times, int binNum, int startHour,
		int& firstBin, vector<double>& binValues)
	{
		firstBin = 0;
		binValues.resize(binNum, 0);

		int len = times.size();
		int currentBin = 0;
		int i = 0;
		for (auto time : times)
		{
			int hour = get_hour(time);
			hour = (hour - startHour + 24) % 24; //时间偏移
			currentBin = bin_index(hour, binNum, 0, 24);
			binValues[currentBin] += 1.0 / len;
			if (i == 0)
			{
				firstBin = currentBin;
			}
			i++;
		}
	}

	void ExtractBins() 
	{
		auto& times = info().postsInfo.times;
		int binNum = 6;
		PSCONF(binNum, name()); 
		int startHour = 1;
		PSCONF(startHour, name());

		int firstBin;
		vector<double> binValues;
		extract_bins(times, binNum, startHour, firstBin, binValues);

		ADD_FEATURE(firstBin);
		ADD_FEATURE(binValues);
	}

	void ExtractDeltas()
	{
		auto& times = info().postsInfo.times;
		auto& forums = info().postsInfo.fids;
		auto& tids = info().postsInfo.tids;

		auto deltas = to_delta_rvec(times);
		double mean = ufo::mean(deltas, 0);
		double defaultVar = 10240;
		PSCONF(defaultVar, name());
		double var = ufo::var(deltas, defaultVar);

		ADD_FEATURE(mean);
		ADD_FEATURE(var);
	}

	virtual void extract() override
	{
		ExtractBins();
		ExtractDeltas();
	}

protected:
private:

};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__TIME_EXTRACTOR_H_
