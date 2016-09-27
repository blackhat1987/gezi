/***************************************************************************
 * 
 * Copyright (c) 2012 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file RandForestModel.h
 * @author wangjian(com@baidu.com)
 * @date 2012/10/24 15:55:38
 * @brief 
 *  
 **/



#ifndef  __RANDFORESTMODEL_H_
#define  __RANDFORESTMODEL_H_


#include "Model.h"
#include "Feature.h"
#include "Score.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "stdio.h"
//#include "memory.h"
#include "math.h"
#include "stdlib.h"

using namespace std;
#define RF_BUFFER_LENGTH 1024
typedef struct struct_rf_cls_tree_t
{
	int* nodestatus;	//!< 节点状态 待split, 中间节点, 终结点
	int* splitid;		//!< 节点对应的split特征
	double* splitvalue;	//!< split特征对应的split value
	int* ndstart;		//!< 节点对应于 Index 的开始位置
	int* ndcount;		//!< 节点内元素的个数
	int** cls;			//!< 节点内元素的各个类的频率
	int* lson;			//!< 节点的左儿子
	int* rson;			//!< 节点的右儿子
	int nodesize;		//!< 树的节点个数
} rf_cls_tree_t;		//!< 分类树的结构体

typedef struct struct_rfinfo
{
	int tree_num;		//!< 森林树的个数
	int fea_num;		//!< Feature的数量
	int data_num;		//!< 训练数据的数据量
	int sample_num;		//!< 训练数据的采样量
	int rand_fea_num;	//!< Feature的采样数量
	int forest_type;	//!< 森林的类型，0为分类树
	int cls_num;		//!< 类的数量

	char** cls_label;	//!< 类名
	int rf_min_node_size;	//!< 树停止的条件，节点覆盖的最少的数据量

	char train_filename[RF_BUFFER_LENGTH];	//!< 训练数据的文件名
	char model_filename[RF_BUFFER_LENGTH];
} rfinfo;

typedef struct struct_rf_model_t
{
	rf_cls_tree_t** cls_forest;	//!< 分类森林
	double* feature_average;	//!< Feature在训练数据的平均值
	rfinfo infbox;				//!< Random Forest的配置参数
}rf_model_t;					//!< Random Forest模型的结构体


class RandForestModel : public Model
{
public:
    RandForestModel(const char*, const char* infoPath);
    virtual ~RandForestModel();
    virtual int load(const char*);
    virtual int init(){return 0;}
    virtual int predict(Feature *, Score *);
    virtual void finalize();
private:
    bool has_colon(string item);
    void fill_no_value_aver(double *x_test);
	/*
	* @brief 使用Random Forest模型进行分类预测
	*
	* @param <IN> rf_model : Random Forest模型结构的指针
	* @param <IN> x_test: 测试数据的Feature值
	* @param <OUT> y_predict : 模型预测的分类类号
	* @return=-1 : 预测失败
	* @return=0 : 预测成功
	* */
	int rf_cls_predict(rf_model_t* rf_model, double *x_test, int& ypredict);

	/*
	* @brief 使用Random Forest模型进行分类预测，同时输出预测的类的概率
	*
	* @param <IN> rf_model : Random Forest模型结构的指针
	* @param <IN> x_test: 测试数据的Feature值
	* @param <OUT> y_predict : 模型预测的分类类号
	* @param <OUT> prob : 模型预测的分类类号的概率
	* @return=-1 : 预测失败
	* @return=0 : 预测成功
	* */

	int rf_cls_predict_prob(rf_model_t* rf_model, double *x_test, int& ypredict, double &prob);
	int load_rfinfo(rfinfo* pinfbox, FILE* model_fp);
	/*
	* @brief 从文件中读取Random Forest的模型
	*
	* @param <IN> model_file : 模型文件名
	* @return=NULL : 读取失败
	* @return!=NULL : 读取成功
	* */
	rf_model_t* rf_load_model(const char* model_file);

	/*
	* @brief 释放Random Forest模型
	*
	* @param <IN> rf_model : Random Forest模型的指针
	*
	* */
	void free_model(rf_model_t*& rf_model);


	/*
	* @brief 计算单棵分类树的预测分类号
	*
	* @param <IN> x_test : 预测数据的Feature值
	* @param <IN> cls_tree : 分类树的指针
	* @param <IN> ypred : 分类类号
	* @return=-1 : 分类失败
	* @return=0 : 分类成功
	* */
	int rf_cls_tree_predict(double *x_test, rf_cls_tree_t *cls_tree, int cls_num, int& ypred);


	/*
	* @brief 加载回归森林
	*
	* @param <IN> model_fp : 模型文件指针
	* @param <IN> rf_model : 模型指针
	* @return=-1 : 加载失败
	* @return=0 : 加载成功
	* */
	int rf_load_cls_forest(FILE* model_fp, rf_model_t* rf_model);

    rf_model_t*  rf_model;
	
};


#endif  //__RANDFORESTMODEL_H_

