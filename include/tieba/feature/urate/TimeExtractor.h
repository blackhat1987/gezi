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


protected:
private:

};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__TIME_EXTRACTOR_H_
