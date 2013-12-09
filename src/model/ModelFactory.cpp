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
#include <string.h>

Model* ModelFactory::createModel(const char* modelType, const char* modelPath, const char* infoPath)
{
    if(!strcmp(modelType, "LinearModel"))
    {
        Model* model = new LinearModel(modelPath, infoPath);
        return model;
    }
    if(!strcmp(modelType, "SvmModel"))
    {
        Model* model = new SvmModel(modelPath, infoPath);
        return model;
    }
    if(!strcmp(modelType, "RandForestModel"))
    {
        Model* model = new RandForestModel(modelPath, infoPath);
        return model;
    }
    return NULL;
}







/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
