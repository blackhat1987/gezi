/**
 *  ==============================================================================
 *
 *          \file   FeatureExtractorMgr.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-12-09 10:21:51.525505
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FEATURE_EXTRACTOR_MGR_H_
#define FEATURE_EXTRACTOR_MGR_H_

#include "FeatureExtractor.h"
namespace gezi
{

class FeatureExtractorMgr
{
public:

  void add(FeatureExtractor* extractor)
  {
    _extractors.push_back(extractor);
  }

  void extract(Feature* feature)
  {
#ifndef NDEBUG
    int i = 0;
#endif
    foreach(FeatureExtractor* extractor, _extractors)
    {
#ifndef NDEBUG
      AutoTimer timer(STRING(i) + " " + extractor->name());
      i++;
#endif 
      extractor->process(feature);
    }
    feature->finalize();
  }

  FeatureExtractor* extractor()
  {
    return _extractors.back();
  }
private:
  vector<FeatureExtractor*> _extractors;
};
}

#endif  //----end of FEATURE_EXTRACTOR_MGR_H_
