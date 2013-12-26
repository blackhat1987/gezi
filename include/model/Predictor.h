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

class Predictor
{
public:

  virtual ~Predictor()
  {
    for (size_t i = 0; i < getModelCnt(); i++)
    {
      delete getModel(i);
      FeatureNormalizer* filter = getNormalizer(i);
      FREE(filter);
    }
  }

  int predict(Feature *, Score *, int index);

  double predict(Feature*, int index);

  double predict(Feature&, int index);

  double predict(string featureStr, int index);

  virtual int init();

  virtual size_t getModelCnt() const
  {
    return modelList_.size();
  }

  Model* model()
  {
    return modelList_[0].second;
  }

  virtual Model* getModel(int index) const
  {
    for (int i = 0; i < (int) modelList_.size(); i++)
    {
      if (modelList_[i].first == index)
      {
        return modelList_[i].second;
      }
    }
    return NULL;
  }

  FeatureNormalizer* normalizer()
  {
    return filterList_[0].second;
  }

  virtual FeatureNormalizer* getNormalizer(int index) const
  {
    for (int i = 0; i < (int) filterList_.size(); i++)
    {
      if (filterList_[i].first == index)
      {
        return filterList_[i].second;
      }
    }
    return NULL;
  }

private:

  void addModel(int id, Model* model)
  {
    modelList_.push_back(make_pair(id, model));
  }

  void addNormalizer(int id, FeatureNormalizer* filter)
  {
    filterList_.push_back(make_pair(id, filter));
  }

  vector< pair<int, Model*> > modelList_;

  vector< pair<int, FeatureNormalizer*> > filterList_;
};


#endif  //__LINEARPREDICTOR_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
