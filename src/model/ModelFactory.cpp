
#include "LinearModel.h"
#include "SvmModel.h"
#include "ModelFactory.h"
#include "RandForestModel.h"
//#include "BinaryFastRankModel.h" //@TODO Ŀǰfastrank ʹ�����������������ݵķ�ʽ ��ʱ����
#include <string.h>

Model* ModelFactory::createModel(const char* modelType, const char* modelPath, const char* infoPath)
{
  Model* model;
  if (!strcasecmp(modelType, "Linear"))
  {
    model = new LinearModel(modelPath, infoPath);
  }
  else if (!strcasecmp(modelType, "Svm") || !strcasecmp(modelType, "LibSvm"))
  { //ע��TODO  ������libsvm��ʽ��LinerSvm KernelSvm ����
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
