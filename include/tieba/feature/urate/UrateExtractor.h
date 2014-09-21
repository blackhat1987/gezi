/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/UrateExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-11 11:49:01.757362
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__URATE_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__URATE_EXTRACTOR_H_
#include "tieba/urate/extended_urate_info.h"
#include "tieba/urate/get_urate_info.h"
#include "feature/Features.h"
namespace gezi {
	namespace tieba {

		//@TODO 是否需要一个模板类 FeaturesWithDtaExtractor static T& info()
		class UrateExtractor : public FeaturesExtractor
		{
		public:
			UrateExtractor(string name)
				:FeaturesExtractor(name)
			{

			}
			static size_t size()
			{
				return info().historySize;
			}

			static int type()
			{
				return info().Type();
			}

			bool IsThread()
			{
				return info().Type() == 1;
			}

			static size_t original_size()
			{
				return info().size();
			}
		public:
			static ExtendedUrateInfo& info()
			{
				static thread_local ExtendedUrateInfo _info;
				return _info;
			}
			ExtendedUrateInfo& _info = info(); //can simply use this
		};
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__URATE_EXTRACTOR_H_
