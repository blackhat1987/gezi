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
	int* nodestatus;	//!< �ڵ�״̬ ��split, �м�ڵ�, �ս��
	int* splitid;		//!< �ڵ��Ӧ��split����
	double* splitvalue;	//!< split������Ӧ��split value
	int* ndstart;		//!< �ڵ��Ӧ�� Index �Ŀ�ʼλ��
	int* ndcount;		//!< �ڵ���Ԫ�صĸ���
	int** cls;			//!< �ڵ���Ԫ�صĸ������Ƶ��
	int* lson;			//!< �ڵ�������
	int* rson;			//!< �ڵ���Ҷ���
	int nodesize;		//!< ���Ľڵ����
} rf_cls_tree_t;		//!< �������Ľṹ��

typedef struct struct_rfinfo
{
	int tree_num;		//!< ɭ�����ĸ���
	int fea_num;		//!< Feature������
	int data_num;		//!< ѵ�����ݵ�������
	int sample_num;		//!< ѵ�����ݵĲ�����
	int rand_fea_num;	//!< Feature�Ĳ�������
	int forest_type;	//!< ɭ�ֵ����ͣ�0Ϊ������
	int cls_num;		//!< �������

	char** cls_label;	//!< ����
	int rf_min_node_size;	//!< ��ֹͣ���������ڵ㸲�ǵ����ٵ�������

	char train_filename[RF_BUFFER_LENGTH];	//!< ѵ�����ݵ��ļ���
	char model_filename[RF_BUFFER_LENGTH];
} rfinfo;

typedef struct struct_rf_model_t
{
	rf_cls_tree_t** cls_forest;	//!< ����ɭ��
	double* feature_average;	//!< Feature��ѵ�����ݵ�ƽ��ֵ
	rfinfo infbox;				//!< Random Forest�����ò���
}rf_model_t;					//!< Random Forestģ�͵Ľṹ��


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
	* @brief ʹ��Random Forestģ�ͽ��з���Ԥ��
	*
	* @param <IN> rf_model : Random Forestģ�ͽṹ��ָ��
	* @param <IN> x_test: �������ݵ�Featureֵ
	* @param <OUT> y_predict : ģ��Ԥ��ķ������
	* @return=-1 : Ԥ��ʧ��
	* @return=0 : Ԥ��ɹ�
	* */
	int rf_cls_predict(rf_model_t* rf_model, double *x_test, int& ypredict);

	/*
	* @brief ʹ��Random Forestģ�ͽ��з���Ԥ�⣬ͬʱ���Ԥ�����ĸ���
	*
	* @param <IN> rf_model : Random Forestģ�ͽṹ��ָ��
	* @param <IN> x_test: �������ݵ�Featureֵ
	* @param <OUT> y_predict : ģ��Ԥ��ķ������
	* @param <OUT> prob : ģ��Ԥ��ķ�����ŵĸ���
	* @return=-1 : Ԥ��ʧ��
	* @return=0 : Ԥ��ɹ�
	* */

	int rf_cls_predict_prob(rf_model_t* rf_model, double *x_test, int& ypredict, double &prob);
	int load_rfinfo(rfinfo* pinfbox, FILE* model_fp);
	/*
	* @brief ���ļ��ж�ȡRandom Forest��ģ��
	*
	* @param <IN> model_file : ģ���ļ���
	* @return=NULL : ��ȡʧ��
	* @return!=NULL : ��ȡ�ɹ�
	* */
	rf_model_t* rf_load_model(const char* model_file);

	/*
	* @brief �ͷ�Random Forestģ��
	*
	* @param <IN> rf_model : Random Forestģ�͵�ָ��
	*
	* */
	void free_model(rf_model_t*& rf_model);


	/*
	* @brief ���㵥�÷�������Ԥ������
	*
	* @param <IN> x_test : Ԥ�����ݵ�Featureֵ
	* @param <IN> cls_tree : ��������ָ��
	* @param <IN> ypred : �������
	* @return=-1 : ����ʧ��
	* @return=0 : ����ɹ�
	* */
	int rf_cls_tree_predict(double *x_test, rf_cls_tree_t *cls_tree, int cls_num, int& ypred);


	/*
	* @brief ���ػع�ɭ��
	*
	* @param <IN> model_fp : ģ���ļ�ָ��
	* @param <IN> rf_model : ģ��ָ��
	* @return=-1 : ����ʧ��
	* @return=0 : ���سɹ�
	* */
	int rf_load_cls_forest(FILE* model_fp, rf_model_t* rf_model);

    rf_model_t*  rf_model;
	
};


#endif  //__RANDFORESTMODEL_H_

