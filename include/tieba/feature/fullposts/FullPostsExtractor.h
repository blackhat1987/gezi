/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/fullposts/FullPostsExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 22:39:59.839975
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_FULLPOSTS__FULL_POSTS_EXTRACTOR_H_
#define TIEBA_FEATURE_FULLPOSTS__FULL_POSTS_EXTRACTOR_H_
#include "tieba/fullposts/extended_fullposts_info.h"
#include "feature/Features.h"
namespace gezi {
	namespace tieba {

		class FullPostsExtractor : public FeaturesExtractor
		{
		public:
			FullPostsExtractor(string name)
				:FeaturesExtractor(name)
			{

			}
		public:
			static ExtendedFullPostsInfo& info()
			{
				static thread_local ExtendedFullPostsInfo _info;
				return _info;
			}
			ExtendedFullPostsInfo& _info = info();
		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_FULLPOSTS__FULL_POSTS_EXTRACTOR_H_
