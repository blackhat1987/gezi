/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/SundryExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-11 11:59:57.442051
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE__SUNDRY_EXTRACTOR_H_
#define TIEBA_FEATURE__SUNDRY_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
	namespace tieba {

		class SundryExtractor : public UrateExtractor
		{
		public:
			SundryExtractor(string name = "Sundry")
				:UrateExtractor(name)
			{

			}

			virtual void extract() override
			{
				//当前帖子是主题还是回复 TODO 目前不考虑楼中楼
				add(type(), "PostType");
				//统计用户总的历史数目(过滤后的)也就是 最近N天发帖量 并且不超过我们设置的最多历史数目
				add(size(), "HistorySize");

				{//主题数目
					int numThreads = from(info().postsInfo.isThreads) >> where([](bool a) { return a == true; }) >> count();
					double threadRatio = numThreads / (double)size();
					ADD_FEATURE(numThreads);
					ADD_FEATURE(threadRatio);
				}
				{//考虑回复对应的主题 出现的distinct主题情况
					int numDistinctThread = distinct_count(info().postsInfo.tids);
					double distinctThreadRatio = numDistinctThread / (double)size();
					ADD_FEATURE(numDistinctThread);
					ADD_FEATURE(distinctThreadRatio);
				}
			}
		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__SUNDRY_EXTRACTOR_H_
