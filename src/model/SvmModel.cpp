/***************************************************************************
 * 
 * Copyright (c) 2012 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/



/**
 * @file src/SvmModel.cpp
 * @author weizheng(com@baidu.com)
 * @date 2012/07/24 17:24:41
 * @brief 
 *  
 **/

#include "SvmModel.h"
//#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using gezi::fnode_t;
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))
#define Free(a) if(a){free(a);a=NULL;}
#define DEFAULT_LINE_LEN 1024

typedef float Qfloat;

/*
#ifndef min
template <class T> static inline T min(T x,T y) { return (x<y)?x:y; }
#endif
#ifndef max
template <class T> static inline T max(T x,T y) { return (x>y)?x:y; }
#endif
#ifndef swap
template <class T> static inline void swap(T& x, T& y) { T t=x; x=y; y=t; }
#endif
 */
template <class S, class T> static inline void clone(T*& dst, S* src, int n)
{
  dst = new T[n];
  memcpy((void *) dst, (void *) src, sizeof (T) * n);
}

/*
 *
 * @return: base的times次方
 */
static inline double powi(double base, int times)
{
  double tmp = base, ret = 1.0;

  for (int t = times; t > 0; t /= 2)
  {
    if (t % 2 == 1) ret *= tmp;
    tmp = tmp * tmp;
  }
  return ret;
}

static const char *svm_type_table[] = {
  "c_svc", "nu_svc", "one_class", "epsilon_svr", "nu_svr", NULL
};

static const char *kernel_type_table[] = {
  "linear", "polynomial", "rbf", "sigmoid", "precomputed", NULL
};

/*
 *
 * @return: input文件句柄中当前位置的一行
 */
static char* readline(FILE *input)
{
  int len;

  char *line = Malloc(char, DEFAULT_LINE_LEN);
  int max_line_len = DEFAULT_LINE_LEN;

  if (fgets(line, max_line_len, input) == NULL)
    return NULL;

  while (strrchr(line, '\n') == NULL)
  {
    max_line_len *= 2;
    line = (char *) realloc(line, max_line_len);
    len = (int) strlen(line);
    if (fgets(line + len, max_line_len - len, input) == NULL)
      break;
  }

  return line;
}

/**
 * 
 *
 */
class QMatrix
{
public:
  virtual Qfloat *get_Q(int column, int len) const = 0;
  virtual double *get_QD() const = 0;
  virtual void swap_index(int i, int j) const = 0;

  virtual ~QMatrix()
  {
  }
};

class Kernel : public QMatrix
{
public:
  Kernel(int l, svm_node * const * x, const svm_parameter& param);
  virtual ~Kernel();

  static double k_function(const svm_node *x, const svm_node *y,
          const svm_parameter& param);
  virtual Qfloat *get_Q(int column, int len) const = 0;
  virtual double *get_QD() const = 0;

  virtual void swap_index(int i, int j) const // no so const...
  {
    swap(x[i], x[j]);
    if (x_square) swap(x_square[i], x_square[j]);
  }
protected:

  double (Kernel::*kernel_function)(int i, int j) const;

private:
  const svm_node **x;
  double *x_square;

  // svm_parameter
  const int kernel_type;
  const int degree;
  const double gamma;
  const double coef0;

  static double dot(const svm_node *px, const svm_node *py);

  double kernel_linear(int i, int j) const
  {
    return dot(x[i], x[j]);
  }

  double kernel_poly(int i, int j) const
  {
    return powi(gamma * dot(x[i], x[j]) + coef0, degree);
  }

  double kernel_rbf(int i, int j) const
  {
    return exp(-gamma * (x_square[i] + x_square[j] - 2 * dot(x[i], x[j])));
  }

  double kernel_sigmoid(int i, int j) const
  {
    return tanh(gamma * dot(x[i], x[j]) + coef0);
  }

  double kernel_precomputed(int i, int j) const
  {
    return x[i][(int) (x[j][0].value)].value;
  }
};

Kernel::Kernel(int l, svm_node * const * x_, const svm_parameter& param)
: kernel_type(param.kernel_type), degree(param.degree),
gamma(param.gamma), coef0(param.coef0)
{
  switch (kernel_type) {
    case LINEAR:
      kernel_function = &Kernel::kernel_linear;
      break;
    case POLY:
      kernel_function = &Kernel::kernel_poly;
      break;
    case RBF:
      kernel_function = &Kernel::kernel_rbf;
      break;
    case SIGMOID:
      kernel_function = &Kernel::kernel_sigmoid;
      break;
    case PRECOMPUTED:
      kernel_function = &Kernel::kernel_precomputed;
      break;
  }

  clone(x, x_, l);

  if (kernel_type == RBF)
  {
    x_square = new double[l];
    for (int i = 0; i < l; i++)
      x_square[i] = dot(x[i], x[i]);
  }
  else
    x_square = 0;
}

Kernel::~Kernel()
{
  delete[] x;
  delete[] x_square;
}

double Kernel::dot(const svm_node *px, const svm_node *py)
{
  double sum = 0;
  while (px->index != -1 && py->index != -1)
  {
    if (px->index == py->index)
    {
      sum += px->value * py->value;
      ++px;
      ++py;
    }
    else
    {
      if (px->index > py->index)
        ++py;
      else
        ++px;
    }
  }
  return sum;
}

double Kernel::k_function(const svm_node *x, const svm_node *y,
        const svm_parameter& param)
{
  switch (param.kernel_type) {
    case LINEAR:
      return dot(x, y);
    case POLY:
      return powi(param.gamma * dot(x, y) + param.coef0, param.degree);
    case RBF:
    {
      double sum = 0;
      while (x->index != -1 && y->index != -1)
      {
        if (x->index == y->index)
        {
          double d = x->value - y->value;
          sum += d*d;
          ++x;
          ++y;
        }
        else
        {
          if (x->index > y->index)
          {
            sum += y->value * y->value;
            ++y;
          }
          else
          {
            sum += x->value * x->value;
            ++x;
          }
        }
      }

      while (x->index != -1)
      {
        sum += x->value * x->value;
        ++x;
      }

      while (y->index != -1)
      {
        sum += y->value * y->value;
        ++y;
      }

      return exp(-param.gamma * sum);
    }
    case SIGMOID:
      return tanh(param.gamma * dot(x, y) + param.coef0);
    case PRECOMPUTED: //x: test (validation), y: SV
      return x[(int) (y->value)].value;
    default:
      return 0; // Unreachable 
  }
}

SvmModel::~SvmModel()
{
  finalize();
}

SvmModel::SvmModel(const char* path, const char *infoPath)
{
  init();
  if (load(path) < 0)
  {
    LOG(FATAL) << "svm model: failed to load model from path: " << path;
    exit(-1);
  }
  LOG(INFO) << "svm model: finish loading model from path: " << path;
}

int SvmModel::init()
{
  memset(&model_, 0, sizeof (model_));
  return 0;
}

int SvmModel::load(const char* path)
{
  FILE *fp = fopen(path, "rb");
  if (fp == NULL)
  {
    return -1;
  }

  char *old_locale = strdup(setlocale(LC_ALL, NULL));
  setlocale(LC_ALL, "C");

  // read parameters

  svm_model *model = &model_;
  svm_parameter& param = model->param;
  model->rho = NULL;
  model->probA = NULL;
  model->probB = NULL;
  model->label = NULL;
  model->nSV = NULL;

  char cmd[81];
  while (1)
  {
    fscanf(fp, "%80s", cmd);

    if (strcmp(cmd, "svm_type") == 0)
    {
      fscanf(fp, "%80s", cmd);
      int i;
      for (i = 0; svm_type_table[i]; i++)
      {
        if (strcmp(svm_type_table[i], cmd) == 0)
        {
          param.svm_type = i;
          break;
        }
      }
      if (svm_type_table[i] == NULL)
      {
        LOG_FATAL("svm model: unknown svm type");

        setlocale(LC_ALL, old_locale);
        Free(old_locale);
        Free(model->rho);
        Free(model->label);
        Free(model->nSV);
        return -1;
      }
    }
    else if (strcmp(cmd, "kernel_type") == 0)
    {
      fscanf(fp, "%80s", cmd);
      int i;
      for (i = 0; kernel_type_table[i]; i++)
      {
        if (strcmp(kernel_type_table[i], cmd) == 0)
        {
          param.kernel_type = i;
          break;
        }
      }
      if (kernel_type_table[i] == NULL)
      {
        LOG_FATAL("svm model: unknown kernel function");

        setlocale(LC_ALL, old_locale);
        Free(old_locale);
        Free(model->rho);
        Free(model->label);
        Free(model->nSV);
        return -1;
      }
    }
    else if (strcmp(cmd, "degree") == 0)
      fscanf(fp, "%d", &param.degree);
    else if (strcmp(cmd, "gamma") == 0)
      fscanf(fp, "%lf", &param.gamma);
    else if (strcmp(cmd, "coef0") == 0)
      fscanf(fp, "%lf", &param.coef0);
    else if (strcmp(cmd, "nr_class") == 0)
      fscanf(fp, "%d", &model->nr_class);
    else if (strcmp(cmd, "total_sv") == 0)
      fscanf(fp, "%d", &model->l);
    else if (strcmp(cmd, "rho") == 0)
    {
      int n = model->nr_class * (model->nr_class - 1) / 2;
      model->rho = Malloc(double, n);
      for (int i = 0; i < n; i++)
        fscanf(fp, "%lf", &model->rho[i]);
    }
    else if (strcmp(cmd, "one_class_bound") == 0)
    {
      fscanf(fp, "%lf", &model->one_class_lower_bound);
      fscanf(fp, "%lf", &model->one_class_upper_bound);

      LOG_DEBUG("one class lower_bound=%f upper_bound=%f", model->one_class_lower_bound, model->one_class_upper_bound);

    }
    else if (strcmp(cmd, "label") == 0)
    {
      int n = model->nr_class;
      model->label = Malloc(int, n);
      for (int i = 0; i < n; i++)
        fscanf(fp, "%d", &model->label[i]);
    }
    else if (strcmp(cmd, "probA") == 0)
    {
      int n = model->nr_class * (model->nr_class - 1) / 2;
      model->probA = Malloc(double, n);
      for (int i = 0; i < n; i++)
        fscanf(fp, "%lf", &model->probA[i]);
    }
    else if (strcmp(cmd, "probB") == 0)
    {
      int n = model->nr_class * (model->nr_class - 1) / 2;
      model->probB = Malloc(double, n);
      for (int i = 0; i < n; i++)
        fscanf(fp, "%lf", &model->probB[i]);
    }
    else if (strcmp(cmd, "nr_sv") == 0)
    {
      int n = model->nr_class;
      model->nSV = Malloc(int, n);
      for (int i = 0; i < n; i++)
        fscanf(fp, "%d", &model->nSV[i]);
    }
    else if (strcmp(cmd, "SV") == 0)
    {
      while (1)
      {
        int c = getc(fp);
        if (c == EOF || c == '\n') break;
      }
      break;
    }
    else
    {
      LOG_FATAL("svm model: unknown text in model file: [%s]", cmd);

      setlocale(LC_ALL, old_locale);
      Free(old_locale);
      Free(model->rho);
      Free(model->label);
      Free(model->nSV);
      return -1;
    }
  }

  // read sv_coef and SV

  int elements = 0;
  long pos = ftell(fp);

  int max_line_len = DEFAULT_LINE_LEN;
  char *line = Malloc(char, max_line_len);
  char *p, *endptr, *idx, *val;

  while ((line = readline(fp)) != NULL)
  {
    p = strtok(line, ":");
    while (1)
    {
      p = strtok(NULL, ":");
      if (p == NULL)
        break;
      ++elements;
    }
    Free(line);
  }

  elements += model->l;

  fseek(fp, pos, SEEK_SET);

  int m = model->nr_class - 1;
  int l = model->l;
  model->sv_coef = Malloc(double *, m);
  int i;
  for (i = 0; i < m; i++)
    model->sv_coef[i] = Malloc(double, l);
  model->SV = Malloc(svm_node*, l);
  svm_node *x_space = NULL;
  if (l > 0) x_space = Malloc(svm_node, elements);

  int j = 0;
  for (i = 0; i < l; i++)
  {
    line = readline(fp);
    model->SV[i] = &x_space[j];

    p = strtok(line, " \t");
    model->sv_coef[0][i] = strtod(p, &endptr);
    for (int k = 1; k < m; k++)
    {
      p = strtok(NULL, " \t");
      model->sv_coef[k][i] = strtod(p, &endptr);
    }

    while (1)
    {
      idx = strtok(NULL, ":");
      val = strtok(NULL, " \t");

      if (val == NULL)
        break;
      x_space[j].index = (int) strtol(idx, &endptr, 10);
      x_space[j].value = strtod(val, &endptr);

      ++j;
    }
    x_space[j++].index = -1;
    Free(line);
  }

  setlocale(LC_ALL, old_locale);
  Free(old_locale);

  if (ferror(fp) != 0 || fclose(fp) != 0)
    return -1;

  model->free_sv = 1; // XXX

  return 0;

}

static double sigmoid_predict(double decision_value, double A, double B)
{
  double fApB = decision_value * A + B;
  // 1-p used later; avoid catastrophic cancellation
  if (fApB >= 0)
    return exp(-fApB) / (1.0 + exp(-fApB));
  else
    return 1.0 / (1 + exp(fApB));
}

// Method 2 from the multiclass_prob paper by Wu, Lin, and Weng

static void multiclass_probability(int k, double **r, double *p)
{
  int t, j;
  int iter = 0, max_iter = max(100, k);
  double **Q = Malloc(double *, k);
  double *Qp = Malloc(double, k);
  double pQp, eps = 0.005 / k;

  for (t = 0; t < k; t++)
  {
    p[t] = 1.0 / k; // Valid if k = 1
    Q[t] = Malloc(double, k);
    Q[t][t] = 0;
    for (j = 0; j < t; j++)
    {
      Q[t][t] += r[j][t] * r[j][t];
      Q[t][j] = Q[j][t];
    }
    for (j = t + 1; j < k; j++)
    {
      Q[t][t] += r[j][t] * r[j][t];
      Q[t][j] = -r[j][t] * r[t][j];
    }
  }
  for (iter = 0; iter < max_iter; iter++)
  {
    // stopping condition, recalculate QP,pQP for numerical accuracy
    pQp = 0;
    for (t = 0; t < k; t++)
    {
      Qp[t] = 0;
      for (j = 0; j < k; j++)
        Qp[t] += Q[t][j] * p[j];
      pQp += p[t] * Qp[t];
    }
    double max_error = 0;
    for (t = 0; t < k; t++)
    {
      double error = fabs(Qp[t] - pQp);
      if (error > max_error)
        max_error = error;
    }
    if (max_error < eps) break;

    for (t = 0; t < k; t++)
    {
      double diff = (-Qp[t] + pQp) / Q[t][t];
      p[t] += diff;
      pQp = (pQp + diff * (diff * Q[t][t] + 2 * Qp[t])) / (1 + diff) / (1 + diff);
      for (j = 0; j < k; j++)
      {
        Qp[j] = (Qp[j] + diff * Q[t][j]) / (1 + diff);
        p[j] /= (1 + diff);
      }
    }
  }
  if (iter >= max_iter)
  {
    LOG_WARNING("svm model: svm model exceeds max_iter in multiclass_prob");
  }
  for (t = 0; t < k; t++) Free(Q[t]);
  Free(Q);
  Free(Qp);
}

double svm_predict_values(const svm_model *model, const svm_node *x, double* dec_values)
{
  int i;
  if (model->param.svm_type == ONE_CLASS ||
          model->param.svm_type == EPSILON_SVR ||
          model->param.svm_type == NU_SVR)
  {
    double *sv_coef = model->sv_coef[0];
    double sum = 0;
    for (i = 0; i < model->l; i++)
      sum += sv_coef[i] * Kernel::k_function(x, model->SV[i], model->param);
    sum -= model->rho[0];
    *dec_values = sum;
    return sum;
  }
  else
  {
    int nr_class = model->nr_class;
    int l = model->l;

    double *kvalue = Malloc(double, l);
    for (i = 0; i < l; i++)
      kvalue[i] = Kernel::k_function(x, model->SV[i], model->param);

    int *start = Malloc(int, nr_class);
    start[0] = 0;
    for (i = 1; i < nr_class; i++)
      start[i] = start[i - 1] + model->nSV[i - 1];

    int *vote = Malloc(int, nr_class);
    for (i = 0; i < nr_class; i++)
      vote[i] = 0;

    int p = 0;
    for (i = 0; i < nr_class; i++)
      for (int j = i + 1; j < nr_class; j++)
      {
        double sum = 0;
        int si = start[i];
        int sj = start[j];
        int ci = model->nSV[i];
        int cj = model->nSV[j];

        int k;
        double *coef1 = model->sv_coef[j - 1];
        double *coef2 = model->sv_coef[i];
        for (k = 0; k < ci; k++)
          sum += coef1[si + k] * kvalue[si + k];
        for (k = 0; k < cj; k++)
          sum += coef2[sj + k] * kvalue[sj + k];
        sum -= model->rho[p];
        dec_values[p] = sum;

        if (dec_values[p] > 0)
          ++vote[i];
        else
          ++vote[j];
        p++;
      }

    int vote_max_idx = 0;
    for (i = 1; i < nr_class; i++)
      if (vote[i] > vote[vote_max_idx])
        vote_max_idx = i;

    Free(kvalue);
    Free(start);
    Free(vote);
    return model->label[vote_max_idx];
  }
}

double svm_predict(const svm_model *model, const svm_node *x)
{
  int nr_class = model->nr_class;
  double *dec_values;
  if (model->param.svm_type == ONE_CLASS ||
          model->param.svm_type == EPSILON_SVR ||
          model->param.svm_type == NU_SVR)
    dec_values = Malloc(double, 1);
  else
    dec_values = Malloc(double, nr_class * (nr_class - 1) / 2);
  double pred_result = svm_predict_values(model, x, dec_values);
  Free(dec_values);
  return pred_result;
}

double svm_predict_probability(
        const svm_model *model, const svm_node *x, double *prob_estimates)
{
  if ((model->param.svm_type == C_SVC || model->param.svm_type == NU_SVC) &&
          model->probA != NULL && model->probB != NULL)
  {
    int i;
    int nr_class = model->nr_class;
    double *dec_values = Malloc(double, nr_class * (nr_class - 1) / 2);
    svm_predict_values(model, x, dec_values);

    double min_prob = 1e-7;
    double **pairwise_prob = Malloc(double *, nr_class);
    for (i = 0; i < nr_class; i++)
      pairwise_prob[i] = Malloc(double, nr_class);
    int k = 0;
    for (i = 0; i < nr_class; i++)
      for (int j = i + 1; j < nr_class; j++)
      {
        pairwise_prob[i][j] = min(max(sigmoid_predict(dec_values[k], model->probA[k], model->probB[k]), min_prob), 1 - min_prob);
        pairwise_prob[j][i] = 1 - pairwise_prob[i][j];
        k++;
      }
    multiclass_probability(nr_class, pairwise_prob, prob_estimates);

    int prob_max_idx = 0;
    for (i = 1; i < nr_class; i++)
      if (prob_estimates[i] > prob_estimates[prob_max_idx])
        prob_max_idx = i;
    for (i = 0; i < nr_class; i++)
      Free(pairwise_prob[i]);
    Free(dec_values);
    Free(pairwise_prob);
    return model->label[prob_max_idx];
  }
  else
    return svm_predict(model, x);
}

double svm_get_svr_probability(const svm_model *model)
{
  if ((model->param.svm_type == EPSILON_SVR || model->param.svm_type == NU_SVR) &&
          model->probA != NULL)
  {
    return model->probA[0];
  }
  else
  {
    LOG_WARNING("svm model: model doesn't contain information for SVR probability inference");
    return 0;
  }
}

int SvmModel::predict(Feature *ftr, Score *scr)
{
  if (NULL == ftr || NULL == scr)
  {
    LOG_WARNING("svm model: illegal feature vector or score buffer for model[%d]", getModelId());
    return -1;
  }

  svm_model *model = &model_;
  int svm_type = model->param.svm_type;
  int nr_class = model->nr_class;
  double *prob_estimates = NULL;
  double predict_label;

  vector<fnode_t> fvector = ftr->cnodes();
  fvector.push_back(fnode_t(-1, 0));
  svm_node *x = &(fvector[0]);

  if (svm_type == C_SVC || svm_type == NU_SVC)
  {
    prob_estimates = (double *) malloc(nr_class * sizeof (double));
    predict_label = svm_predict_probability(model, x, prob_estimates);
    for (int j = 0; j < nr_class; j++)
    {
      scr->addItem(prob_estimates[j]);
    }
  }
  else if (svm_type == NU_SVR || svm_type == EPSILON_SVR)
  {
    double prob = svm_get_svr_probability(model);
    predict_label = svm_predict(model, x);
    scr->addItem(predict_label);
    scr->addItem(prob);
  }
  else if (svm_type == ONE_CLASS)
  {
    double predict_value = svm_predict(model, x);
    LOG_DEBUG("svm model: one class predict value=%lf", predict_value);
    double prob = 1 - (predict_value - model->one_class_lower_bound) / (model->one_class_upper_bound - model->one_class_lower_bound);
    prob = max(0., prob);
    prob = min(1., prob);
    scr->addItem(prob);
  }

  Free(prob_estimates);

  return 0;
}

void SvmModel::predict(Feature& ft, vector<double>& result)
{
  Feature* ftr = &ft;
  svm_model *model = &model_;
  int svm_type = model->param.svm_type;
  int nr_class = model->nr_class;
  double *prob_estimates = NULL;
  double predict_label;

  vector<fnode_t> fvector = ftr->cnodes();
  fvector.push_back(fnode_t(-1, 0));
  svm_node *x = &(fvector[0]);

  if (svm_type == C_SVC || svm_type == NU_SVC)
  {
    prob_estimates = (double *) malloc(nr_class * sizeof (double));
    predict_label = svm_predict_probability(model, x, prob_estimates);
    for (int j = 0; j < nr_class; j++)
    {
      result.push_back(prob_estimates[j]);
    }
    PVEC(result);
  }
  else if (svm_type == NU_SVR || svm_type == EPSILON_SVR)
  {
    double prob = svm_get_svr_probability(model);
    predict_label = svm_predict(model, x);
    result.push_back(predict_label);
    result.push_back(prob);
  }
  else if (svm_type == ONE_CLASS)
  {
    double predict_value = svm_predict(model, x);
    LOG_DEBUG("svm model: one class predict value=%lf", predict_value);
    double prob = 1 - (predict_value - model->one_class_lower_bound) / (model->one_class_upper_bound - model->one_class_lower_bound);
    prob = max(0., prob);
    prob = min(1., prob);
    result.push_back(prob);
  }

  Free(prob_estimates);
}

void SvmModel::finalize()
{
  svm_model *model = &model_;
  svm_destroy_param(&(model->param));
  svm_free_model_content(model);
}

void svm_free_model_content(svm_model* model_ptr)
{
  if (model_ptr->free_sv && model_ptr->l > 0 && model_ptr->SV != NULL)
  {
    void *temp = (void *) (model_ptr->SV[0]);
    Free(temp);
  }
  if (model_ptr->sv_coef)
  {
    for (int i = 0; i < model_ptr->nr_class - 1; i++)
      Free(model_ptr->sv_coef[i]);
  }

  Free(model_ptr->SV);
  model_ptr->SV = NULL;

  Free(model_ptr->sv_coef);
  model_ptr->sv_coef = NULL;

  Free(model_ptr->rho);
  model_ptr->rho = NULL;

  Free(model_ptr->label);
  model_ptr->label = NULL;

  Free(model_ptr->probA);
  model_ptr->probA = NULL;

  Free(model_ptr->probB);
  model_ptr->probB = NULL;

  Free(model_ptr->nSV);
  model_ptr->nSV = NULL;
}


void svm_destroy_param(svm_parameter* param)
{
  Free(param->weight_label);
  Free(param->weight);
}

int svm_check_probability_model(const svm_model *model)
{
  return ((model->param.svm_type == C_SVC || model->param.svm_type == NU_SVC) &&
          model->probA != NULL && model->probB != NULL) ||
          ((model->param.svm_type == EPSILON_SVR || model->param.svm_type == NU_SVR) &&
          model->probA != NULL);
}


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
