/**
 *  ==============================================================================
 *
 *          \file   gain_summary.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-07-23 17:18:03.119728
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef GAIN_SUMMARY_H_
#define GAIN_SUMMARY_H_
#include "common_util.h"
namespace gezi {

	inline string gain_summary(const map<int, double>& m, bool normalize = true)
	{
		//@TODO
		//vector<pair<int, double> > sortedByGain = sort_map_by_value_reverse(m);
		//auto sortedByGain = sort_map_by_value_reverse(m);
		vector<pair<int, double> > sortedByGain;
		sort_map_by_value_reverse(m, sortedByGain);
		double maxValue = sortedByGain[0].second;
		double normalizingFactor = (normalize && (maxValue != 0.0)) ? std::sqrt(maxValue) : 1.0;
		double power = normalize ? 0.5 : 1.0;

		stringstream ss;
		int id = 0;
		for (auto item : sortedByGain)
		{
			ss << setiosflags(ios::left) << setfill(' ') << setw(40)
				<< STR(id++) + ":" + featureList[item.first].Name
				<< " " << std::pow(item.second, power) / normalizingFactor << endl;
		}
		return ss.str();
	}

}  //----end of namespace gezi

#endif  //----end of GAIN_SUMMARY_H_
