/***************************************************************************
 * 
 * Copyright (c) 2012 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file ModelFactory.cpp
 * @author weizheng(com@baidu.com)
 * @date 2012/05/22 22:29:03
 * @brief 
 *  
 **/

#include "LinearModel.h"
#include "SvmModel.h"
#include "ModelFactory.h"
#include "RandForestModel.h"
#include "FastRankModel.h"
#include <string.h>

Model* ModelFactory::createModel(const char* modelType, const char* modelPath, const char* infoPath)
{
  Model* model;
  if (!strcasecmp(modelType, "Linear"))
  {
    model = new LinearModel(modelPath, infoPath);
  }
  else if (!strcasecmp(modelType, "Svm") || !strcasecmp(modelType, "LibSvm"))
  { //注意TODO  包括非libsvm形式的LinerSvm KernelSvm 可能
    model = new SvmModel(modelPath, infoPath);
  }
  else if (!strcasecmp(modelType, "RandForest") || !strcasecmp(modelType, "RandomForest"))
  {
    model = new RandForestModel(modelPath, infoPath);
  }
  else if (!strcasecmp(modelType, "FastRank"))
  {
    model = new FastRankModel();
  }
  else
  {
    return NULL;
  }
  model->setModelType(modelType);
  model->setModelPath(modelPath);
  return model;
}







/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
