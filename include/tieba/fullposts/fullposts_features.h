/**
 *  ==============================================================================
 *
 *          \file   tieba/fullposts/fullposts_features.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 22:38:14.031726
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FULLPOSTS_FULLPOSTS_FEATURES_H_
#define TIEBA_FULLPOSTS_FULLPOSTS_FEATURES_H_

#include "feature/Features.h"
#include "tieba/feature/fullposts/DingtieExtractor.h"
#include "tieba/feature/fullposts/SequenceExtractor.h"

namespace gezi {
namespace tieba {
	inline void add_fullposts_features(FeaturesExtractorMgr& mgr)
	{
		mgr.add(new DingtieExtractor);
		mgr.add(new FPSequenceExtractor);
	}
}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FULLPOSTS_FULLPOSTS_FEATURES_H_
