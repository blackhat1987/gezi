/***************************************************************************
 * 
 * Copyright (c) 2012 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file Predictor.cpp
 * @author weizheng(com@baidu.com)
 * @date 2012/03/31 20:01:53
 * @brief 
 *  
 **/

#include "Predictor.h"
#include "Feature.h"
#include "Score.h"
#include "ModelFactory.h"

#include "log_util.h"
#include "conf_util.h"
#include "common_util.h"
#include "debug_util.h"
#include <string.h>

DEFINE_string(model, "", "首个模型地址,如果不为空覆盖conf值");
DEFINE_string(norm, "", "首个模型文件地址,如果不为空覆盖conf值");
DEFINE_string(model_dir, "", "首个模型dir 如果不为空则下面的 model，norm覆盖掉conf值");
DEFINE_string(model_type, "libsvm", "模型类型");

int Predictor::init()
{
  string section = "Predictor";
  int model_cnt = 1;
  SCONF(model_cnt);
  CHECK_GE(model_cnt, 1);

  Pval(FLAGS_model_dir);
  Pval(model_cnt);
  for (int i = 0; i < model_cnt; i++)
  {
    string modelDir, modelPath, modelInfoPath;

    if (i == 0 && !FLAGS_model_dir.empty())
    {
      modelPath = (format("%s/feature.%s.model") % FLAGS_model_dir % FLAGS_model_type).str();
      modelInfoPath = (format("%s/feature.%s.range") % FLAGS_model_dir % FLAGS_model_type).str();
    }
    else
    {
      {
        string name = (format("model_%d_dir") % i).str();
        gezi::set_val(gezi::SharedConf::conf(), section, gezi::conf_trim(name), modelDir);
      }
      if (!modelDir.empty())
      {
        modelPath = (format("%s/feature.%s.model") % modelDir % FLAGS_model_type).str();
        modelInfoPath = (format("%s/feature.%s.range") % modelDir % FLAGS_model_type).str();
      }
      else
      {
        {
          string name = (format("model_%d_path") % i).str();
          gezi::set_val(gezi::SharedConf::conf(), section, gezi::conf_trim(name), modelPath);
        }
        if (i == 0 && !FLAGS_model.empty())
        {
          modelPath = FLAGS_model;
        }
        CHECK_NE(modelPath.empty(), true);

        {
          string name = (format("normalize_info_%d_path") % i).str();
          gezi::set_val(gezi::SharedConf::conf(), section, gezi::conf_trim(name), modelInfoPath);
        }
        if (i == 0 && !FLAGS_norm.empty())
        {
          modelInfoPath = FLAGS_norm;
        }
      }
    }

    LOG(INFO) << format("load model_%d_path [%s] done!") % i % modelPath;
    LOG(INFO) << format("load normalize_info_%d_path [%s] done!") % i % modelInfoPath;

    string modelType = "LibSvm";
    if (i == 0 && !FLAGS_model_type.empty())
    {
      LOG(INFO) << "Using FLAGS_model_type " << FLAGS_model_type;
      modelType = FLAGS_model_type;
    }
    else
    {
      string name = (format("model_%d_type") % i).str();
      gezi::set_val(gezi::SharedConf::conf(), section, gezi::conf_trim(name), modelType);
    }
    CHECK_NE(modelType.empty(), true);
    LOG(INFO) << format("load model_%d_type [%s] done!") % i % modelType;

    FeatureNormalizer* filter = NULL;

    if (!modelInfoPath.empty())
    {

      filter = new FeatureNormalizer();

      if (!filter->open(modelInfoPath.c_str()))
      {
        LOG(WARNING) << "normalize file not open " << modelInfoPath;
      }
    }

    addNormalizer(filter);
    LOG(INFO) << format("add filter for model type[%s], model infopath[%s] done!") % modelType % modelInfoPath;

    Model* model = ModelFactory::createModel(modelType.c_str(), modelPath.c_str(), modelInfoPath.c_str());

    if (model == NULL)
    {
      LOG(WARNING) << "could not create model from model factory you need to add your specific model manualy";
      return -1;
    }

    model->setModelId(i);
    addModel(model);
    LOG(INFO) << format("add model for model type[%s], model path[%s] done!") % modelType % modelPath;
  }

  return 0;

}

int Predictor::predict(Feature* feature, Score* score, int index)
{
  Model* model = getModel(index);
  CHECK_NOTNULL(model);
  FeatureNormalizer * normalizer = getNormalizer(index);

  if (normalizer)
  {

    normalizer->normalize(feature);
  }

  return model->predict(feature, score);
}

double Predictor::predict(Feature* feature, int index, int inner_index)
{
  Model* model = getModel(index);
  CHECK_NOTNULL(model);
  //Predictor.cpp:124: undefined reference to `FLAG__namespace_do_not_use_directly_use_DECLARE_int32_instead::FLAGS_v'
  //比较奇怪 未找到原因 https://code.google.com/p/server1/issues/detail?id=1 可能是链接glog gflags顺序?
  //但是如果用DLOG(INFO)没有问题 怀疑是bug
  //  Pval(model->getModelPath());  
#ifndef NDEBUG
  model->printInfo();
#endif
  FeatureNormalizer * normalizer = getNormalizer(index);

  if (normalizer)
  {
    normalizer->normalize(feature);
  }
  PVAL(*feature);
  return model->predict(feature, inner_index);
}

double Predictor::predict(Feature& feature, int index, int inner_index)
{

  return predict(&feature, index, inner_index);
}

void Predictor::predict(Feature* feature, vector<Score>* result)
{
  int modelNum = _modelList.size();
  (*result).resize(modelNum);
  for (int i = 0; i < modelNum; i++)
  {
    predict(feature, &(*result)[i], i);
  }
}

//use this one!

void Predictor::predict(Feature& feature, vector<double>& result, int index)
{
  if (index >= _modelList.size())
  {
    LOG(WARNING) << "index too big: " << index << " model num: " << _modelList.size();
    return;
  }
  if (index < 0)
  {
    int modelNum = _modelList.size();
    PVAL(modelNum);
    for (int i = 0; i < modelNum; i++)
    {
      PVAL(_modelList[i]->type());
      Feature fe = feature;
      FeatureNormalizer * normalizer = getNormalizer(i);
      if (normalizer)
      {
        normalizer->normalize(&fe);
      }
      _modelList[i]->predict(fe, result);
    }
  }
  else
  {
    FeatureNormalizer * normalizer = getNormalizer(index);
    if (normalizer)
    {
      normalizer->normalize(&feature);
    }
    PVAL(_modelList[index]->type());
    _modelList[index]->predict(feature, result);
  }
}

void Predictor::predict(Feature& feature, vector<vector<double> >& result)
{
  int modelNum = _modelList.size();
  for (int i = 0; i < modelNum; i++)
  {
    vector<double> vec;
    _modelList[i]->predict(feature, vec);
    result.push_back(vec);
  }
}

#include "feature_util.h"

double Predictor::predict(string featureStr, int index, int inner_index)
{
  Feature feature = gezi::to_feature(featureStr);
  return predict(&feature, index, inner_index);
}

void Predictor::predict(string featureStr, vector<Score>& result)
{
  Feature feature = gezi::to_feature(featureStr);
  int modelNum = _modelList.size();
  result.resize(modelNum);

  predict(&feature, &result);
}

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
