/***************************************************************************
 *
 * Copyright (c) 2012 Baidu.com, Inc. All Rights Reserved
 *
 **************************************************************************/



/**
 * @file LinearModel.h
 * @author weizheng(com@baidu.com)
 * @date 2012/03/30 14:54:48
 * @brief
 *
 **/



#ifndef  __LINEARMODEL_H_
#define  __LINEARMODEL_H_


#include "Model.h"
#include "Feature.h"
#include "Score.h"
using gezi::fnode_t;

enum { L2R_LR, L2R_L2LOSS_SVC_DUAL, L2R_L2LOSS_SVC, L2R_L1LOSS_SVC_DUAL, MCSVM_CS, L1R_L2LOSS_SVC, L1R_LR, L2R_LR_DUAL };

/*
 * 模型参数
 *
 */
typedef struct model_
{
	int solver_type; // 模型训练的类型，
	int nr_class; // 类别数量
	int nr_feature; //特征维数
	int *label; // 类标签
	double bias; //是否有w0
	double *w; //各个特征的权重
}model_t;

class LinearModel : public Model
{
public:
	LinearModel(const char*, const char* infoPath);
	virtual ~LinearModel();
	virtual int load(const char*);
	virtual int init(){ return 0; }
	virtual int predict(Feature *, Score *);
	virtual void finalize();
private:
	int predict_values(const vector<fnode_t> &, double *);
	int predict_probability(const vector<fnode_t> &, double*);

	model_t model_;
	int wcnt_; //各个特征的权重系数的数量，取决于是否有bias

};


#endif  //__LINEARMODEL_H_


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
