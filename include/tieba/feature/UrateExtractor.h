/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/UrateExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-10 12:03:12.823147
 *
 *  \Description:   主要处理Urate相关的数据
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE__URATE_EXTRACTOR_H_
#define TIEBA_FEATURE__URATE_EXTRACTOR_H_
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
protected:
	static ExtendedUrateInfo& info()
	{
		static thread_local ExtendedUrateInfo _urateInfo;
		return _urateInfo;
	}
private:
};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE__URATE_EXTRACTOR_H_
