/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/NumberExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-12 07:56:48.907357
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__NUMBER_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__NUMBER_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
	namespace tieba {


		class NumberExtractor : public UrateExtractor
		{
		public:
			NumberExtractor(string name = "Number")
				:UrateExtractor(name)
			{

			}

			virtual void init() override
			{
				info().ExtractNumbers();
				info().ExtractNormedNumbers();
			}

		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__NUMBER_EXTRACTOR_H_
