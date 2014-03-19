/**
 *  ==============================================================================
 *
 *          \file   FeatureExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-12-09 10:21:40.973448
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FEATURE_EXTRACTOR_H_
#define FEATURE_EXTRACTOR_H_
#include "Feature.h"
#include "feature/feature_util.h"
namespace gezi
{

class FeatureExtractor
{
public:
  //每个FeatureExtractor类对应有一个名字

  FeatureExtractor(string name = "")
  : _name(name)
  {

  }

  virtual ~FeatureExtractor()
  {

  }

  //获取资源数据或者数据预处理

  virtual void init()
  {

  }

  //特征抽取部分

  virtual void extract()
  {

  }

  void bind(Feature* feature)
  {
    _feature = feature;
  }

  virtual void process(Feature* feature)
  {
    bind(feature);
    _feature->add_section(_name);
    init();
    extract();
  }

  string name()
  {
    return _name;
  }

  inline Feature* feature()
  {
    return _feature;
  }

  inline void add(double value, const string& name = "")
  {
    _feature->add(value, name);
  }
	
	template<typename Vec>
  inline void add(Vec& values, const string& name = "")
  {
    _feature->add(values, name);
  }

  inline void add(double* values, int n, const string& name = "")
  {
    _feature->add(values, n, name);
  }

protected:
  string _name;
  Feature* _feature;
};
}
#endif  //----end of FEATURE_EXTRACTOR_H_
