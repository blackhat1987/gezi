/***************************************************************************
 * 
 * Copyright (c) 2012 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file ../include/ModelFactory.h
 * @author weizheng(com@baidu.com)
 * @date 2012/05/22 22:31:08
 * @brief 
 *  
 **/


#ifndef  ____MODELFACTORY_H_
#define  ____MODELFACTORY_H_


#include "Model.h"
#include <string>

class ModelFactory
{
public:
  static Model* createModel(const char* modelType, const char* modelPath, const char* infoPath);

  static Model* createModel(const std::string& modelType, const std::string& modelPath, string infoPath)
  {
    return createModel(modelType.c_str(), modelPath.c_str(), infoPath.c_str());
  }
};




#endif  //____/INCLUDE/MODELFACTORY_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
