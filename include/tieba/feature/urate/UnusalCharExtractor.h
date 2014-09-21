/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/UnusalCharExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-17 14:12:26.904177
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__UNUSAL_CHAR_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__UNUSAL_CHAR_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
namespace tieba {

class UnusalCharExtractor : public UrateExtractor
{
public:
	UnusalCharExtractor(string name = "UnusalChar")
		:UrateExtractor(name)
	{

	}

	virtual void init() override
	{
		info().ExtractGbkDualContents();
	}

	virtual void extract() override
	{
		ivec totalCountVec = from(info().gbkDualContents) >> select([](string content) { return (int)content.length() / 2; }) >> to_vector();
		ivec unusualCharCountVec = from(info().gbkDualContents) >> select([](string content) { return (int)extract_suspect_symb(content).size() / 2; }) >> to_vector();
		int sumTotalCountVec = sum(totalCountVec);
		int sumUnusualCharCountVec = sum(unusualCharCountVec);

		double nowUnusualCharRatio = (1 + unusualCharCountVec[0]) / (double)(1 + totalCountVec[0]);
		double unusualCharRatio = (1 + sumUnusualCharCountVec) / (double)(1 + sumTotalCountVec);
		ADD_FEATURE(nowUnusualCharRatio);
		ADD_FEATURE(unusualCharRatio);
	}
protected:
private:

};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__UNUSAL_CHAR_EXTRACTOR_H_
