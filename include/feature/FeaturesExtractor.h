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
 //ÿ��FeatureExtractor���Ӧ��һ������
	FeaturesExtractor(string name = "")
	: _name(name)
	{

	}

	virtual ~FeaturesExtractor()
	{

	}

	//��ȡ��Դ���ݻ�������Ԥ����
	virtual void init()
	{

	}

	//������ȡ����
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

	//@TODO remove ���ݾɵĽӿ�
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
