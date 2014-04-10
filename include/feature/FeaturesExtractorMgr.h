/**
 *  ==============================================================================
 *
 *          \file   feature/FeaturesExtractorMgr.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-04-10 15:55:17.030190
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FEATURE__FEATURES_EXTRACTOR_MGR_H_
#define FEATURE__FEATURES_EXTRACTOR_MGR_H_

#include "feature/FeaturesExtractor.h"
namespace gezi {

class FeaturesExtractorMgr 
{
public:
	virtual ~FeaturesExtractorMgr()
  {
    for(FeaturesExtractor* extractor : _extractors)
    {
      FREE(extractor);
    }
  }

  void add(FeaturesExtractor* extractor)
  {
    _extractors.push_back(extractor);
  }
	
	void extract(Features& features)
	{
		extract(&features);
	}

  void extract(Features* features)
  {
#ifndef NDEBUG
    int i = 0;
#endif

    for(FeaturesExtractor* extractor : _extractors)
    {
#ifndef NDEBUG
      AutoTimer timer(STRING(i) + " " + extractor->name());
      i++;
#endif 
      //      VLOG(4) << STRING(i) << " " << extractor->name() << " begin";
      extractor->process(features);
      //      VLOG(4) << STRING(i) << " " << extractor->name() << " end";
    }
    features->finalize();
  }
	
  FeaturesExtractor* extractor()
  {
    return _extractors.back();
  }

  vector<FeaturesExtractor*>& extractors()
  {
    return _extractors;
  }

	const vector<FeaturesExtractor*>& extractors() const
  {
    return _extractors;
  }
private:
  vector<FeaturesExtractor*> _extractors;
};
}  //----end of namespace gezi

#endif  //----end of FEATURE__FEATURES_EXTRACTOR_MGR_H_
