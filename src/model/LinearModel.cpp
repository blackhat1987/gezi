/***************************************************************************
 * 
 * Copyright (c) 2012 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file LinearModel.cpp
 * @author weizheng(com@baidu.com)
 * @date 2012/03/30 14:57:42
 * @brief 
 *
 * 线性分类回归模型，支持Logistic Regression和Linear SVM 的预测
 * 基于 Liblinear
 *  
 **/

#include "LinearModel.h"
#include "log_util.h"

#define Calloc(type,n) (type *)calloc((n),sizeof(type))
#define Free(p) if(p){free(p);p=NULL;}

/*
 * 模型的类型
 */
static const char *solver_type_table[] ={
  "L2R_LR", "L2R_L2LOSS_SVC_DUAL", "L2R_L2LOSS_SVC", "L2R_L1LOSS_SVC_DUAL", "MCSVM_CS",
  "L1R_L2LOSS_SVC", "L1R_LR", "L2R_LR_DUAL", NULL
};

LinearModel::LinearModel(const char* path, const char* infoPath)
{
  if (load(path) < 0)
  {
    LOG_FATAL("linear model: failed to load model from path[%s]", path);
    exit(-1);
  }

}

LinearModel::~LinearModel()
{
  finalize();
}

/**
 * 加载模型
 *
 */
int LinearModel::load(const char* path)
{
  LOG_DEBUG("loading model from path[%s]...", path);

  FILE *fp = fopen(path, "r");
  if (fp == NULL)
  {
    LOG_FATAL("linear model: open model file [%s] failed", path);
    return -1;
  }

  int i;
  int nr_feature;
  int n;
  int nr_class;
  double bias;

  model_.label = NULL;

  char cmd[81];
  while (1)
  {
    fscanf(fp, "%80s", cmd);
    if (strcmp(cmd, "solver_type") == 0)
    {
      fscanf(fp, "%80s", cmd);
      int i;
      for (i = 0; solver_type_table[i]; i++)
      {
        if (strcmp(solver_type_table[i], cmd) == 0)
        {
          model_.solver_type = i;
          break;
        }
      }
      if (solver_type_table[i] == NULL)
      {
        LOG_FATAL("linear model: unknown solver type");
        return -1;
      }
    }
    else if (strcmp(cmd, "nr_class") == 0)
    {
      fscanf(fp, "%d", &nr_class);
      model_.nr_class = nr_class;
    }
    else if (strcmp(cmd, "nr_feature") == 0)
    {
      fscanf(fp, "%d", &nr_feature);
      model_.nr_feature = nr_feature;
    }
    else if (strcmp(cmd, "bias") == 0)
    {
      fscanf(fp, "%lf", &bias);
      model_.bias = bias;
    }
    else if (strcmp(cmd, "w") == 0)
    {
      break;
    }
    else if (strcmp(cmd, "label") == 0)
    {
      int nr_class = model_.nr_class;
      model_.label = Calloc(int, nr_class);
      if (model_.label == NULL)
      {
        LOG_FATAL("linear model: can not malloc memory");
        return -1;
      }
      for (int i = 0; i < nr_class; i++)
      {
        fscanf(fp, "%d", &(model_.label[i]));
      }
    }
    else
    {
      LOG_FATAL("linear model: unknown text in model file: [%s]", cmd);
      return -1;
    }
  }

  nr_feature = model_.nr_feature;
  if (model_.bias >= 0)
  {
    n = nr_feature + 1;
  }
  else
  {
    n = nr_feature;
  }
  wcnt_ = n;
  int w_size = n;
  int nr_w;
  if (nr_class == 2 && model_.solver_type != MCSVM_CS)
  {
    nr_w = 1;
  }
  else
  {
    nr_w = nr_class;
  }

  model_.w = Calloc(double, w_size * nr_w);
  for (i = 0; i < w_size; i++)
  {
    int j;
    for (j = 0; j < nr_w; j++)
    {
      fscanf(fp, "%lf ", &model_.w[i * nr_w + j]);
    }
    fscanf(fp, "\n");
  }
  if (ferror(fp) != 0 || fclose(fp) != 0)
  {
    LOG_FATAL("linear model: failed to close model file");
    return -1;
  }
  else
  {
    LOG_TRACE("linear model: load model file done");
  }
  return 0;
}

/*
 *@param fvector: 输入特征向量
 *@param dec_values: 每个分类对应的计算权值
 *@ret 正常为0，异常小于0
 *
 */
int LinearModel::predict_values(const vector<fnode_t> &fvector, double *dec_values)
{
  double *w = model_.w;
  int nr_class = model_.nr_class;
  int nr_w;
  if (nr_class == 2 && model_.solver_type != MCSVM_CS)
  {
    nr_w = 1;
  }
  else
  {
    nr_w = nr_class;
  }

  for (int i = 0; i < nr_w; i++)
  {
    for (int j = 0; j < (int) fvector.size(); j++)
    {
      int w_index = (fvector[j].index - 1) * nr_w + i;
      if (w_index >= wcnt_ * nr_w || w_index < 0)
      {
        LOG_WARNING("linear model: input vector index out of bounds, vector length[%d] index[%d]", wcnt_, w_index);
      }
      else
      {
        dec_values[i] += w[w_index] * fvector[j].value;
      }
    }
  }

  return 0;

}

/**
 *
 *@param fvector: 输入特征向量
 *@param prob_estimates: 每个分类对应的概率值
 *@ret: 正常为0，异常小于0
 */
int LinearModel::predict_probability(const vector<fnode_t> &fvector, double* prob_estimates)
{
  int i;
  int nr_class = model_.nr_class;
  int nr_w;

  if (nr_class == 2)
  {
    nr_w = 1;
  }
  else
  {
    nr_w = nr_class;
  }

  if (predict_values(fvector, prob_estimates) < 0)
  {
    LOG_WARNING("linear model: failed to predict values");
    return -1;
  }
  for (i = 0; i < nr_w; i++)
  {
    prob_estimates[i] = 1 / (1 + exp(-prob_estimates[i]));
  }

  if (nr_class == 2) // for binary classification
  {
    prob_estimates[1] = 1. - prob_estimates[0];
  }
  else
  {
    double sum = 0;
    for (i = 0; i < nr_class; i++)
      sum += prob_estimates[i];

    for (i = 0; i < nr_class; i++)
      prob_estimates[i] = prob_estimates[i] / sum;
  }

  return 0;
}

/*
 *@param ftr: 输入特征 
 *@param scr: 输出分值
 *@ret: 正常为0，异常为负
 */
int LinearModel::predict(Feature *ftr, Score *scr)
{
  if (NULL == ftr || NULL == scr)
  {
    LOG_WARNING("linear model: illegal feature vector or score buffer");
    return -1;
  }

  vector<fnode_t>& fvector = ftr->nodes();

  /**
   * check valid
   */
  for (int i = 0; i < (int) fvector.size(); i++)
  {
    if (fvector[i].index > model_.nr_feature)
    {
      fvector[i].value = 0;
    }
  }

  if (model_.bias > 0)
  {
    fvector.push_back(fnode_t(model_.nr_feature + 1, model_.bias));
  }

  double *prob_estimates = Calloc(double, model_.nr_class);
  if (prob_estimates == NULL)
  {
    LOG_WARNING("linear model: failed to allocate memory");
    return -1;
  }

  if (predict_probability(fvector, prob_estimates) < 0)
  {
    LOG_WARNING("linear model: failed to predict probability");
    Free(prob_estimates);
    return -1;
  }

  for (int i = 0; i < model_.nr_class; i++)
  {
    scr->addItem(prob_estimates[i]);
  }

  Free(prob_estimates);

  return 0;
}

void LinearModel::finalize()
{
  Free(model_.label);
  Free(model_.w);

}



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
