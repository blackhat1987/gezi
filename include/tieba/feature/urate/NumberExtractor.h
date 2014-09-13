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

			virtual void extract() override
			{
				int numNmbers = non_empty_count(info().numbersVec);
				int numNormedNumbers = non_empty_count(info().normedNumbersVec);
				ADD_FEATURE(numNmbers);
				ADD_FEATURE(numNormedNumbers);
				double normedNumberRatio = (1 + numNmbers) / (double)(1 + numNormedNumbers);
				ADD_FEATURE(normedNumberRatio);
				double numberRatio = numNormedNumbers / (double)size();
				ADD_FEATURE(numberRatio);
				int numDistinctNumbers = distinct_count_vec2d(info().normedNumbersVec);
				ADD_FEATURE(numDistinctNumbers);
				double distinctNumberRatio = (1 + numDistinctNumbers) / (double)(1 + numNormedNumbers);
				ADD_FEATURE(distinctNumberRatio);
			}
		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__NUMBER_EXTRACTOR_H_
