/***************************************************************************
 * 
 * Copyright (c) 2012 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file Predictor.h
 * @author weizheng(com@baidu.com)
 * @date 2012/03/31 19:57:50
 * @brief 
 *  
 **/



#ifndef  __PREDICTOR_H_
#define  __PREDICTOR_H_

#include "Model.h"
#include "feature/FeatureNormalizer.h"
#include <vector>
using gezi::FeatureNormalizer;

//对model的进一步封装 支持多个model统一管理打分
class Predictor
{
public:
  typedef vector<Model*> ModelList;
  typedef vector<FeatureNormalizer*> NormalizerList;

  virtual ~Predictor()
  {
    for (size_t i = 0; i < getModelCnt(); i++)
    {
      delete getModel(i);
      FeatureNormalizer* filter = getNormalizer(i);
      FREE(filter);
    }
  }

  //index model的索引位置, inner_index score内部索引位置
  int predict(Feature *, Score *, int index = 0);

  double predict(Feature*, int index = 0, int inner_index = 0);

  double predict(Feature&, int index = 0, int inner_index = 0);

  double predict(string featureStr, int index = 0, int inner_index = 0);

  void predict(Feature*, vector<Score>* result);
  
  //use this one! -1 表示使用所有model逐个打分, = 0表示使用第一个model打分
  void predict(Feature&, vector<double>& result, int index = 0);
  
  void predict(Feature&, vector<vector<double> >& result);
  
  void predict(string featureStr, vector<Score>& result);

  virtual int init();

  virtual size_t getModelCnt() const
  {
    return _modelList.size();
  }

  Model* model()
  {
    return _modelList[0];
  }

  virtual Model* getModel(int index) const
  {
    return _modelList[index];
  }

  FeatureNormalizer* normalizer()
  {
    return _filterList[0];
  }

  virtual FeatureNormalizer* getNormalizer(int index) const
  {
    return _filterList[index];
  }

  inline ModelList& modelList()
  {
    return _modelList;
  }

  inline NormalizerList& filterList()
  {
    return _filterList;
  }

  void addModel(Model* model)
  {
    _modelList.push_back(model);
  }

  void addNormalizer(FeatureNormalizer* filter)
  {
    _filterList.push_back(filter);
  }
  
  inline int modelNum()
  {
    return _modelList.size();
  }

private:
  
  ModelList _modelList;

  NormalizerList _filterList;
};


#endif  //__LINEARPREDICTOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
