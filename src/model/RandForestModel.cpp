/***************************************************************************
 * 
 * Copyright (c) 2012 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file RandForestModel.cpp
 * @author wangjian(com@baidu.com)
 * @date 2012/10/24 15:55:38
 * @brief 
 *
 * random Forest分类模型：一种集群学习算法.
 * 基于多棵分类回归树(CART),random体现在训练样本选择和分裂特征选择过程中.
 *  
 **/

#include "RandForestModel.h"
#include "log_util.h"

#define RF_TERMINAL -1
#define RF_NO_VALUE 0x7FFFFFFF
using gezi::fnode_t;
RandForestModel::RandForestModel(const char* path, const char* infoPath)
{
  if (load(path) < 0)
  {
    ul_writelog(UL_LOG_FATAL, "random-forest model: failed to load model from path[%s]", path);
    exit(-1);
  }

}

RandForestModel::~RandForestModel()
{
  finalize();
}

/**
 * 加载模型
 */
int RandForestModel::load(const char* path)
{
  LOG_DEBUG("loading model from path[%s]...", path);

  rf_model = rf_load_model(path);
  if (rf_model == NULL)
  {
    LOG_FATAL("Training model failed!\n");
    return -1;
  }

  return 0;
}


//int main(int argc, char* argv[])

int RandForestModel::predict(Feature *ftr, Score *scr)
{
  if (NULL == ftr || NULL == scr)
  {
    ul_writelog(UL_LOG_WARNING, "linear model: illegal feature vector or score buffer");
    return -1;
  }
  vector<fnode_t>& fvector = ftr->nodes();
  int len = (int) fvector.size();


  double *x_test = (double*) malloc(rf_model->infbox.fea_num * sizeof (double));
  if (x_test == NULL)
  {
    LOG_FATAL("Failed to allocate memory.");
    free_model(rf_model);
    return -1;
  }

  for (int j = 0; j < rf_model->infbox.fea_num; j++)
    x_test[j] = RF_NO_VALUE;

  int cls_predict = 0;
  double prob = 0;
  int feat;
  double value = 0;

  for (int i = 0; i < len; i++)
  {
    feat = fvector[i].index; // feature Id
    value = fvector[i].value; // feature value
    x_test[feat] = value;

    LOG_DEBUG("normalized input vector for model id[%d] index[%d] value[%f]", getModelId(), feat, value);
  }

  fill_no_value_aver(x_test);
  LOG_TRACE("forest_type = %d.", rf_model->infbox.forest_type);
  if (rf_model->infbox.forest_type == 0)
  {
    if (rf_cls_predict_prob(rf_model, x_test, cls_predict, prob) == 0) //
    {
      char * cls_label = rf_model->infbox.cls_label[cls_predict];
      LOG_TRACE("RandForest: cls_predict=[%d], cls_label=[%s], prob=[%f]", cls_predict, cls_label, prob);
      int cls_label_num = *cls_label - '0';
      if (0 == cls_label_num)
      {
        scr->addItem(prob);
        scr->addItem(1.0 - prob);
      }
      else
      {
        scr->addItem(1.0 - prob);
        scr->addItem(prob);
      }
    }
    else
    {
      LOG_FATAL("Failed to predict.");
    }
  }

  free(x_test);
  return 0;
}

bool RandForestModel::has_colon(string item)
{
  for (int i = 0; i < (int) item.size(); i++)
  {
    if (item[i] == ':')
      return true;
  }

  return false;
}

void RandForestModel::fill_no_value_aver(double *x_test)
{
  for (int i = 0; i < rf_model->infbox.fea_num; i++)
  {
    if (x_test[i] == RF_NO_VALUE)
      x_test[i] = rf_model->feature_average[i];
  }
}

void RandForestModel::finalize()
{

  free_model(rf_model);

}

int RandForestModel::load_rfinfo(rfinfo* pinfbox, FILE* model_fp)
{
  if (pinfbox == NULL || model_fp == NULL)
  {
    LOG_FATAL("Parameter error.");
    return -1;
  }
  if (fread(&pinfbox->tree_num, sizeof (int), 1, model_fp) != 1)
  {
    LOG_FATAL("Load model file error!");
    return -1;
  }
  if (fread(&pinfbox->fea_num, sizeof (int), 1, model_fp) != 1)
  {
    LOG_FATAL("Load model file error!");
    return -1;
  }

  if (fread(&pinfbox->data_num, sizeof (int), 1, model_fp) != 1)
  {
    LOG_FATAL("Load model file error!");
    return -1;
  }
  if (fread(&pinfbox->sample_num, sizeof (int), 1, model_fp) != 1)
  {
    LOG_FATAL("Load model file error!");
    return -1;
  }

  if (fread(&pinfbox->rand_fea_num, sizeof (int), 1, model_fp) != 1)
  {
    LOG_FATAL("Load model file error!");
    return -1;
  }

  if (fread(&pinfbox->forest_type, sizeof (int), 1, model_fp) != 1)
  {
    LOG_FATAL("Load model file error!");
    return -1;
  }

  if (fread(&pinfbox->cls_num, sizeof (int), 1, model_fp) != 1)
  {
    LOG_FATAL("Load model file error!");
    return -1;
  }

  int len;
  if (pinfbox->forest_type == 0)
  {
    int n = pinfbox->cls_num;

    pinfbox->cls_label = (char**) malloc(n * sizeof (char*));
    if (pinfbox->cls_label == NULL)
    {
      LOG_FATAL("Failed to allocate memory.");
      return -1;
    }
    for (int i = 0; i < n; i++)
    {
      if (fread(&len, sizeof (int), 1, model_fp) != 1)
      {
        LOG_FATAL("Load model file error!");
        return -1;
      }
      pinfbox->cls_label[i] = (char*) malloc((len + 1) * sizeof (char));
      if ((int) fread(pinfbox->cls_label[i], sizeof (char), len + 1, model_fp) != len + 1)
      {
        LOG_FATAL("Load model file error!");
        return -1;
      }
    }
  }

  if (fread(&pinfbox->rf_min_node_size, sizeof (int), 1, model_fp) != 1)
  {
    LOG_FATAL("Load model file error!");
    return -1;
  }

  if (fread(&len, sizeof (int), 1, model_fp) != 1)
  {
    LOG_FATAL("Load model file error!");
    return -1;
  }

  if ((int) fread(pinfbox->train_filename, sizeof (char), len + 1, model_fp) != len + 1)
  {
    LOG_FATAL("Load model file error!");
    return -1;
  }

  return 0;
}

rf_model_t* RandForestModel::rf_load_model(const char* model_file)
{
  if (!model_file)
  {
    LOG_FATAL("Parameter error.");
    return NULL;
  }
  FILE* model_fp = fopen(model_file, "rb");

  if (!model_fp)
  {
    LOG_FATAL("Can't open model file!");
    return NULL;
  }

  rf_model_t* rf_model = (rf_model_t*) calloc(1, sizeof (rf_model_t));
  if (!rf_model)
  {
    LOG_FATAL("Failed to allocate memory.");
    fclose(model_fp);
    return NULL;
  }
  if (load_rfinfo(&rf_model->infbox, model_fp) != 0)
  {
    LOG_FATAL("Load model file error!");
    free_model(rf_model);
    fclose(model_fp);
    return NULL;
  }
  if (rf_model->infbox.forest_type == 0)
  {
    if (rf_load_cls_forest(model_fp, rf_model) == -1)
    {
      LOG_FATAL("Load model file error!");
      free_model(rf_model);
      fclose(model_fp);
      return NULL;
    }
  }

  rf_model->feature_average = (double*) malloc(rf_model->infbox.fea_num * sizeof (double));
  if (rf_model->feature_average == NULL)
  {
    LOG_FATAL("Load model file error!");
    free_model(rf_model);
    fclose(model_fp);
    return NULL;
  }
  if ((int) fread(rf_model->feature_average, sizeof (double), rf_model->infbox.fea_num, model_fp) != rf_model->infbox.fea_num)
  {
    LOG_FATAL("Load model file error!");
    free(rf_model->feature_average);
    free_model(rf_model);
    fclose(model_fp);
    return NULL;
  }

  fclose(model_fp);

  return rf_model;
}

int RandForestModel::rf_cls_predict(rf_model_t* rf_model, double *x_test, int& ypredict)
{
  double prob = 0;

  return rf_cls_predict_prob(rf_model, x_test, ypredict, prob);
}

int RandForestModel::rf_cls_predict_prob(rf_model_t* rf_model, double *x_test, int& ypredict, double &prob)
{
  if (rf_model->cls_forest == NULL || x_test == NULL)
  {
    LOG_FATAL("Parameter error.");
    return -1;
  }

  int* cls = (int*) malloc(rf_model->infbox.cls_num * sizeof (int));
  if (cls == NULL)
  {
    LOG_FATAL("Failed to allocate memory.");
    return -1;
  }

  for (int i = 0; i < rf_model->infbox.cls_num; i++)
  {
    cls[i] = 0;
  }

  for (int i = 0; i < rf_model->infbox.tree_num; i++)
  {
    if (rf_model->cls_forest[i] != NULL)
    {
      int spred = 0;
      if (rf_cls_tree_predict(x_test, rf_model->cls_forest[i], rf_model->infbox.cls_num, spred) != 0)
      {
        return -1;
      }
      cls[spred]++;
    }
  }
  int cls_max = 0;
  for (int i = 0; i < rf_model->infbox.cls_num; i++)
  {
    if (cls_max < cls[i])
    {
      ypredict = i;
      cls_max = cls[i];
    }
  }

  free(cls);

  if (rf_model->infbox.tree_num > 0)
  {
    prob = (double) cls_max / (double) rf_model->infbox.tree_num;
    return 0;
  }
  else
  {
    prob = 0;
    return -1;
  }
}

int RandForestModel::rf_cls_tree_predict(double *x_test, rf_cls_tree_t *cls_tree, int cls_num, int& ypred)
{
  if (x_test == NULL || cls_tree == NULL)
  {
    LOG_FATAL("Parameter error.");
    return -1;
  }

  int k = 0;
  while (cls_tree->nodestatus[k] != RF_TERMINAL)
  { /* go down the tree */
    int m = cls_tree->splitid[k];
    if (x_test[m] <= cls_tree->splitvalue[k])
    {
      k = cls_tree->lson[k];
    }
    else
    {
      k = cls_tree->rson[k];
    }
  }

  int cls_max = 0;

  for (int i = 0; i < cls_num; i++)
  {
    if (cls_max < cls_tree->cls[k][i])
    {
      cls_max = cls_tree->cls[k][i];
      ypred = i;
    }
  }

  return 0;
}

int RandForestModel::rf_load_cls_forest(FILE* model_fp, rf_model_t* rf_model)
{
  if (model_fp == NULL || rf_model == NULL)
  {
    LOG_FATAL("Parameter error.");
    return -1;
  }

  rf_model->cls_forest = (rf_cls_tree_t**) malloc(rf_model->infbox.tree_num * sizeof (rf_cls_tree_t*));
  if (rf_model->cls_forest == NULL)
  {
    LOG_FATAL("Failed to allocate memory.");
    return -1;
  }

  rf_cls_tree_t* prtree;
  int nodesize;
  int rsize;

  if (rf_model->cls_forest == NULL)
  {
    LOG_FATAL("Failed to allocate memory.");
    return -1;
  }

  for (int i = 0; i < rf_model->infbox.tree_num; i++)
  {
    rsize = fread(&nodesize, sizeof (int), 1, model_fp);
    if (rsize != 1)
    {
      LOG_FATAL("Load model file error.");
      return -1;
    }

    rf_model->cls_forest[i] = (rf_cls_tree_t*) malloc(sizeof (rf_cls_tree_t));
    if (rf_model->cls_forest[i] == NULL)
    {
      LOG_FATAL("Failed to allocate memory.");
      return -1;
    }
    prtree = rf_model->cls_forest[i];
    prtree->nodestatus = (int*) malloc(nodesize * sizeof (int));
    if (prtree->nodestatus == NULL)
    {
      LOG_FATAL("Failed to allocate memory.");
      return -1;
    }
    prtree->lson = (int*) malloc(nodesize * sizeof (int));
    if (prtree->lson == NULL)
    {
      LOG_FATAL("Failed to allocate memory.");
      return -1;
    }
    prtree->rson = (int*) malloc(nodesize * sizeof (int));
    if (prtree->rson == NULL)
    {
      LOG_FATAL("Failed to allocate memory.");
      return -1;
    }
    prtree->splitid = (int*) malloc(nodesize * sizeof (int));
    if (prtree->splitid == NULL)
    {
      LOG_FATAL("Failed to allocate memory.");
      return -1;
    }
    prtree->splitvalue = (double*) malloc(nodesize * sizeof (double));
    if (prtree->splitvalue == NULL)
    {
      LOG_FATAL("Failed to allocate memory.");
      return -1;
    }
    prtree->cls = (int**) malloc(nodesize * sizeof (int*));
    if (prtree->cls == NULL)
    {
      LOG_FATAL("Failed to allocate memory.");
      return -1;
    }
    for (int j = 0; j < nodesize; j++)
    {
      prtree->cls[j] = (int*) malloc(rf_model->infbox.cls_num * sizeof (int));
      if (prtree->cls[j] == NULL)
      {
        LOG_FATAL("Failed to allocate memory.");
        return -1;
      }
    }

    prtree->nodesize = nodesize;

    if ((int) fread(prtree->nodestatus, sizeof (int), nodesize, model_fp) != nodesize)
    {
      LOG_FATAL("Load model file error!");
      return -1;
    }
    if ((int) fread(prtree->splitid, sizeof (int), nodesize, model_fp) != nodesize)
    {
      LOG_FATAL("Load model file error!");
      return -1;
    }
    if ((int) fread(prtree->splitvalue, sizeof (double), nodesize, model_fp) != nodesize)
    {
      LOG_FATAL("Load model file error!");
      return -1;
    }

    for (int j = 0; j < nodesize; j++)
    {
      if ((int) fread(prtree->cls[j], sizeof (int), rf_model->infbox.cls_num, model_fp) != rf_model->infbox.cls_num)
      {
        LOG_FATAL("Load model file error!");
        return -1;
      }
    }

    if ((int) fread(prtree->rson, sizeof (int), nodesize, model_fp) != nodesize)
    {
      LOG_FATAL("Load model file error!");
      return -1;
    }
    if ((int) fread(prtree->lson, sizeof (int), nodesize, model_fp) != nodesize)
    {
      LOG_FATAL("Load model file error!");
      return -1;
    }
    prtree->ndstart = NULL;
    prtree->ndcount = NULL;
  }

  return 0;
}

void RandForestModel::free_model(rf_model_t*& rf_model)
{
  if (rf_model == NULL)
  {
    return;
  }

  if (rf_model->infbox.forest_type == 0 && rf_model->cls_forest != NULL)
  {
    rf_cls_tree_t* prtree;
    for (int i = 0; i < rf_model->infbox.tree_num; i++)
    {
      prtree = rf_model->cls_forest[i];
      if (prtree != NULL)
      {
        if (prtree->nodestatus != NULL)
        {
          free(prtree->nodestatus);
          prtree->nodestatus = NULL;
        }
        if (prtree->lson != NULL)
        {
          free(prtree->lson);
          prtree->lson = NULL;
        }
        if (prtree->rson != NULL)
        {
          free(prtree->rson);
          prtree->rson = NULL;
        }
        if (prtree->splitid != NULL)
        {
          free(prtree->splitid);
          prtree->splitid = NULL;
        }
        if (prtree->splitvalue != NULL)
        {
          free(prtree->splitvalue);
          prtree->splitvalue = NULL;
        }
        if (prtree->ndstart != NULL)
        {
          free(prtree->ndstart);
          prtree->ndstart = NULL;
        }
        if (prtree->ndcount != NULL)
        {
          free(prtree->ndcount);
          prtree->ndcount = NULL;
        }
        if (prtree->cls != NULL)
        {
          for (int j = 0; j < rf_model->cls_forest[i]->nodesize; j++)
          {
            if (prtree->cls[j] != NULL)
            {
              free(prtree->cls[j]);
              prtree->cls[j] = NULL;
            }
          }
          free(rf_model->cls_forest[i]->cls);
          rf_model->cls_forest[i]->cls = NULL;
        }
        free(rf_model->cls_forest[i]);
        rf_model->cls_forest[i] = NULL;
      }
    }
    free(rf_model->cls_forest);
    rf_model->cls_forest = NULL;
  }

  if (rf_model->feature_average != NULL)
  {
    free(rf_model->feature_average);
    rf_model->feature_average = NULL;
  }

  for (int i = 0; i < rf_model->infbox.cls_num; i++)
  {
    if (rf_model->infbox.cls_label[i] != NULL)
    {
      free(rf_model->infbox.cls_label[i]);
      rf_model->infbox.cls_label[i] = NULL;
    }
  }
  if (rf_model->infbox.cls_label != NULL)
  {
    free(rf_model->infbox.cls_label);
    rf_model->infbox.cls_label = NULL;
  }

  free(rf_model);
  rf_model = NULL;
}


