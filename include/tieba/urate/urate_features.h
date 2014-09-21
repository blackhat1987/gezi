/**
 *  ==============================================================================
 *
 *          \file   tieba/urate/urate_features.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 22:35:05.534062
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_URATE_URATE_FEATURES_H_
#define TIEBA_URATE_URATE_FEATURES_H_
#include "feature/Features.h"
#include "tieba/feature/urate/SundryExtractor.h"
#include "tieba/feature/urate/UserExtractor.h"
#include "tieba/feature/urate/MediaExtractor.h"
#include "tieba/feature/urate/NumberExtractor.h"
#include "tieba/feature/urate/IpExtractor.h"
#include "tieba/feature/urate/TimeExtractor.h"
#include "tieba/feature/urate/ForumExtractor.h"
#include "tieba/feature/urate/TextExtractor.h"
#include "tieba/feature/urate/UnusalCnExtractor.h"
#include "tieba/feature/urate/UnusalCharExtractor.h"
#include "tieba/feature/urate/TextScoreExtractor.h"
#include "tieba/feature/urate/PlsaTopicExtractor.h"
#include "tieba/feature/urate/TitleSimExtractor.h"
#include "tieba/feature/urate/ContentSimExtractor.h"
#include "tieba/feature/urate/LanguageModelExtractor.h"
#include "tieba/feature/urate/SequenceExtractor.h"
#include "tieba/feature/urate/DictMatchExtractor.h"

namespace gezi {
namespace tieba {

	inline void add_urate_features(FeaturesExtractorMgr& mgr)
	{
		mgr.add(new SundryExtractor);
		mgr.add(new UserExtractor);
		mgr.add(new MediaExtractor);
		mgr.add(new NumberExtractor);
		mgr.add(new IpExtractor);
		mgr.add(new TimeExtractor);
		mgr.add(new ForumExtractor);
		mgr.add(new TextExtractor);
		mgr.add(new UnusalCnExtractor);
		mgr.add(new UnusalCharExtractor);
		mgr.add(new TextScoreExtractor);
		mgr.add(new TextScoreExtractor("RscTextScore", true));
		mgr.add(new PlsaTopicExtractor);
		mgr.add(new TitleSimExtractor);
		mgr.add(new ContentSimExtractor);
		mgr.add(new LanguageModelExtractor);
		mgr.add(new SequenceExtractor);
		mgr.add(new DictMatchExtractor);
	}
}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_URATE_URATE_FEATURES_H_
