/***************************************************************************
 * 
 * Copyright (c) 2012 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file SvmModel.h
 * @author weizheng(com@baidu.com)
 * @date 2012/07/24 14:54:58
 * @brief 
 * 基于LibSVM，支持LibSVM的算法
 *  
 **/

#ifndef  __SVMMODEL_H_
#define  __SVMMODEL_H_

#include "Model.h"

typedef Feature::Node svm_node;
enum
{
  C_SVC, NU_SVC, ONE_CLASS, EPSILON_SVR, NU_SVR
}; /* svm_type */

enum
{
  LINEAR, POLY, RBF, SIGMOID, PRECOMPUTED
}; /* kernel_type */

struct svm_parameter
{
  int svm_type;
  int kernel_type;
  int degree; /* for poly */
  double gamma; /* for poly/rbf/sigmoid */
  double coef0; /* for poly/sigmoid */

  /* these are for training only */
  double cache_size; /* in MB */
  double eps; /* stopping criteria */
  double C; /* for C_SVC, EPSILON_SVR and NU_SVR */
  int nr_weight; /* for C_SVC */
  int *weight_label; /* for C_SVC */
  double* weight; /* for C_SVC */
  double nu; /* for NU_SVC, ONE_CLASS, and NU_SVR */
  double p; /* for EPSILON_SVR */
  int shrinking; /* use the shrinking heuristics */
  int probability; /* do probability estimates */
};

//
// svm_model
// 

struct svm_model
{
  struct svm_parameter param; /* parameter */
  int nr_class; /* number of classes, = 2 in regression/one class svm */
  int l; /* total #SV */
  svm_node **SV; /* SVs (SV[l]) */
  double one_class_lower_bound; /* min sum value for one class classification in the training set */
  double one_class_upper_bound; /* max sum value for one class classification in the training set */
  double **sv_coef; /* coefficients for SVs in decision functions (sv_coef[k-1][l]) */
  double *rho; /* constants in decision functions (rho[k*(k-1)/2]) */
  double *probA; /* pariwise probability information */
  double *probB;

  /* for classification only */

  int *label; /* label of each class (label[k]) */
  int *nSV; /* number of SVs for each class (nSV[k]) */
  /* nSV[0] + nSV[1] + ... + nSV[k-1] = l */
  /* XXX */
  int free_sv; /* 1 if svm_model is created by svm_load_model*/
  /* 0 if svm_model is created by svm_train */
};

struct svm_model *svm_load_model(const char *model_file_name);

double svm_get_svr_probability(const struct svm_model *model);

double svm_predict_values(const struct svm_model *model, const svm_node *x, double* dec_values);
double svm_predict(const struct svm_model *model, const svm_node *x);
double svm_predict_probability(const struct svm_model *model, const svm_node *x, double* prob_estimates);

void svm_free_model_content(struct svm_model *model_ptr);
void svm_destroy_param(struct svm_parameter *param);

class SvmModel : public Model
{
public:
  SvmModel(const char*, const char*);
  virtual ~SvmModel();
  virtual int load(const char*);
  virtual int init();
  virtual int predict(Feature *, Score *);
  virtual void predict(Feature&, vector<double>&);
  virtual void finalize();

private:
  struct svm_model model_;
};



#endif  //__SVMMODEL_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
