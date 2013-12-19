/**
 *  ==============================================================================
 *
 *          \file   SharedPredictor.h
 *
 *        \author   chenghuige
 *
 *          \date   2013-12-09 21:40:33.957375
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef SHARED_PREDICTOR_H_
#define SHARED_PREDICTOR_H_

#include "Predictor.h"

class SharedPredictor
{
public:
  
  static Predictor* instance()
  {
    return &_predictor;
  }

  static void init()
  {
    int ret = _predictor.init();
    Pval(ret);
    CHECK_EQ(ret, 0);
  }
private:
  static Predictor _predictor; 
};


#endif  //----end of SHARED_PREDICTOR_H_
