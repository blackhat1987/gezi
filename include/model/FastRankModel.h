/**
 *  ==============================================================================
 *
 *          \file   FastRankModel.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-09 22:37:47.471980
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FAST_RANK_MODEL_H_
#define FAST_RANK_MODEL_H_
#include "Model.h"

class FastRankModel : public Model
{
  virtual ~FastRankModel()
  {
    
  }
  //virtual int predict(Feature*, Score*);
  //virtual void predict(Feature&, vector<double>&);
};

#endif  //----end of FAST_RANK_MODEL_H_
