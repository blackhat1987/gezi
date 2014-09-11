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
				//统计用户总的历史数目(过滤后的)也就是 最近30天发帖量 同时也是我们实际使用的历史天数
				add(size(), "HistorySize");
			}
		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__SUNDRY_EXTRACTOR_H_
