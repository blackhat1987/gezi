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
      modelPath = FLAGS_model_dir + "/feature.libsvm.model";
      modelInfoPath = FLAGS_model_dir + "/feature.libsvm.range";
    }
    else
    {
      {
        string name = (format("model_%d_dir") % i).str();
        gezi::set_val(gezi::SharedConf::conf(), section, gezi::conf_trim(name), modelDir);
      }
      if (!modelDir.empty())
      {
        modelPath = modelDir + "/feature.libsvm.model";
        modelInfoPath = modelDir + "/feature.libsvm.range";
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

    string modelType = "SvmModel";
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

      CHECK_EQ(filter->open(modelInfoPath.c_str()), true);
    }

    addNormalizer(i, filter);
    LOG(INFO) << format("add filter for model type[%s], model infopath[%s] done!") % modelType % modelInfoPath;

    Model* model = ModelFactory::createModel(modelType.c_str(), modelPath.c_str(), modelInfoPath.c_str());
    CHECK_NOTNULL(model);
    model->setModelId(i);

    addModel(i, model);
    LOG(INFO) << format("add model for model type[%s], model path[%s] done!") % modelType % modelPath;
  }

  return 0;

}

int Predictor::predict(Feature* feature, Score* score, int index = 0)
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

double Predictor::predict(Feature* feature, int index = 0)
{
  Score score;
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

  return model->predict(feature);
}

double Predictor::predict(Feature& feature, int index = 0)
{
  return predict(&feature, index);
}

#include "feature_util.h"

double Predictor::predict(string featureStr, int index = 0)
{
  Feature feature = gezi::to_feature(featureStr);
  return predict(&feature, index);
}



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
