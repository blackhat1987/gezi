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

	void ExtractHoursCovered()
	{
		auto& times = info().originalPostsInfo.times; //不考虑时间限制 总数不超过25个
		int hoursCovered = distinct_count(times, get_hour);
		double hoursCoveredRatio = hoursCovered / (double)times.size();

		ADD_FEATURE(hoursCovered);
		ADD_FEATURE(hoursCoveredRatio);
	}

	static void calc_delta_count(const vector<int64>& deltas, const ivec& intervals, 
		ivec& counts)
	{
		counts.resize(intervals.size(), 0);
		for (auto delta : deltas)
		{
			for (size_t i = 0; i < intervals.size(); i++)
			{
				if (delta <= intervals[i])
				{
					for (size_t j = i; j < intervals.size(); j++)
					{
						counts[j]++;
					}
					break;
				}
			}
		}
	}

	void ExtractDeltaCount(const vector<int64>& deltas, string name = "")
	{
		ivec intervals = { 1, 2, 5, 10, 50, 100 };
		ivec deltaCounts;
		calc_delta_count(deltas, intervals, deltaCounts);
		dvec deltaRatios = from(deltaCounts) >> select([this](int a) { return a / (double)size(); }) >> to_vector();
		ADD_FEATURE_WITH_PREFIX(deltaCounts, name);
		ADD_FEATURE_WITH_PREFIX(deltaRatios, name);
	}

	void ExtractDeltas()
	{
		auto& times = info().postsInfo.times;
		auto& forums = info().postsInfo.fids;
		auto& tids = info().postsInfo.tids;

		auto deltas = to_delta_rvec(times);
		//double deltasMean = ufo::mean(deltas, 0);
		double defaultVar = 1e+10;
		PSCONF(defaultVar, name());
		//double deltasVar = ufo::var(deltas, defaultVar);
		double  deltasMean = 0, deltasVar = defaultVar;
		ufo::mean_var(deltas, deltasMean, deltasVar);
		double deltasMin = ufo::min(deltas, kOneHour);

		auto threadDeltas = to_delta_rvec_when_unequal(times, tids);
		//double threadDeltasMean = ufo::mean(threadDeltas, 0);
		//double threadDeltasVar = ufo::var(threadDeltas, defaultVar);
		double threadDeltasMean = 0, threadDeltasVar = defaultVar;
		ufo::mean_var(threadDeltas, threadDeltasMean, threadDeltasVar);
		double threadDeltasMin = ufo::min(threadDeltas, kOneHour);

		auto forumDeltas = to_delta_rvec_when_unequal(times, forums);
		//double forumDeltasMean = ufo::mean(forumDeltas, 0);
		//double forumDeltasVar = ufo::var(forumDeltas, defaultVar); 
		double forumDeltasMean = 0, forumDeltasVar = defaultVar;
		ufo::mean_var(forumDeltas, forumDeltasMean, forumDeltasVar);
		double forumDeltasMin = ufo::min(forumDeltas, kOneHour);
		
		ADD_FEATURE(deltasMean);
		ADD_FEATURE(deltasVar);
		ADD_FEATURE(deltasMin);

		ADD_FEATURE(threadDeltasMean);
		ADD_FEATURE(threadDeltasVar);
		ADD_FEATURE(threadDeltasMin);

		ADD_FEATURE(forumDeltasMean);
		ADD_FEATURE(forumDeltasVar);
		ADD_FEATURE(forumDeltasMin);

		ExtractDeltaCount(deltas);
		ExtractDeltaCount(threadDeltas, "Thread");
		ExtractDeltaCount(forumDeltas, "Forum");

		int distinctDeltaCount = distinct_count(deltas);
		double distinctDeltaRatio = distinctDeltaCount / (double)size();
		ADD_FEATURE(distinctDeltaCount);
		ADD_FEATURE(distinctDeltaRatio);
	}

	//最大时间间隔前后的行为变化 盗号特征
	void ExtractBehaviorChanges()
	{
		auto& times = info().originalPostsInfo.times;
		auto& forumIds = info().originalPostsInfo.fids;
		info().ExtractOriginalLocations();
		auto& locations = info().originalLocations;

		auto deltas = to_delta_rvec(times);
		//minmax quick but no need..
		int maxDelta = ufo::max(deltas, kOneHour);

		ADD_FEATURE(maxDelta);

		auto iter = ufo::max_element(deltas);
		int maxDeltaPos = iter - deltas.begin() + 1;

		set<uint> forumsAfter, forumsBefore;
		set<string> locationsAfter, locationsBefore;

		for (int i = 0; i < maxDeltaPos; i++)
		{
			forumsAfter.insert(forumIds[i]);
			locationsAfter.insert(locations[i]);
		}

		for (int i = maxDeltaPos; i < (int)original_size(); i++)
		{
			forumsBefore.insert(forumIds[i]);
			locationsBefore.insert(locations[i]);
		}

		int numForumDiffs = ufo::set_symmetric_difference(forumsAfter, forumsBefore).size();
		int numLocationDiffs = ufo::set_symmetric_difference(locationsAfter, locationsBefore).size();

		ADD_FEATURE(numForumDiffs);
		ADD_FEATURE(numLocationDiffs);
	}

	virtual void extract() override
	{
		ExtractBins();
		ExtractDeltas();
		ExtractHoursCovered();
		ExtractBehaviorChanges();
	}

protected:
private:

};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__TIME_EXTRACTOR_H_
