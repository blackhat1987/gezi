/**
 *  ==============================================================================
 *
 *          \file   feature/FeaturesExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-04-10 15:55:02.980722
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FEATURE__FEATURES_EXTRACTOR_H_
#define FEATURE__FEATURES_EXTRACTOR_H_

#include "feature/FeatureVector.h"
#include "feature/features_util.h"
namespace gezi {

class FeaturesExtractor 
{
public:
 //每个FeatureExtractor类对应有一个名字
	FeaturesExtractor(string name = "")
	: _name(name)
	{

	}

	virtual ~FeaturesExtractor()
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

	void bind(Features* features)
	{
		_features = features;
	}

	virtual void process(Features* features)
	{
		bind(features);
		_features->add_section(_name);
		init();
		extract();
	}

	string name()
	{
		return _name;
	}

	Features* features()
	{
		return _features;
	}

	//@TODO remove 兼容旧的接口
	Features* feature()
	{
		return _features;
	}

	void add(double value, string name = "")
	{
		_features->add(value, name);
	}
	
	template<typename Vec>
	void add(Vec& values, string name = "")
	{
		_features->add(values, name);
	}

	void add(double* values, int n, string name = "")
	{
		_features->add(values, n, name);
	}

protected:
	string _name;
	Features* _features;
};

}  //----end of namespace gezi

#endif  //----end of FEATURE__FEATURES_EXTRACTOR_H_
