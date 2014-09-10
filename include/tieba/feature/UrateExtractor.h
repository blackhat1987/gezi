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

class UrateExtractor : public FeaturesExtractor
{
public:
	UrateExtractor() = default;
protected:
private:

};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE__URATE_EXTRACTOR_H_
