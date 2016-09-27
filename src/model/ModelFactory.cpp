
#include "LinearModel.h"
#include "SvmModel.h"
#include "ModelFactory.h"
#include "RandForestModel.h"
//#include "BinaryFastRankModel.h" //@TODO 目前fastrank 使用引入代码而不是数据的方式 暂时这样
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
  /*else if (!strcasecmp(modelType, "BinaryFastRank"))
  {
    model = new BinaryFastRankModel();
  }*/
  else
  {
    return NULL;
  }
  model->setModelType(modelType);
  model->setModelPath(modelPath);
  return model;
}







/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
