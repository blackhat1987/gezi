/**
 *  ==============================================================================
 *
 *          \file   FeatureIdentifer.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-01-19 10:21:59.791620
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FEATURE_IDENTIFER_H_
#define FEATURE_IDENTIFER_H_
#include "Identifer.h"
#include "Matrix.h"
namespace gezi {

class FeatureIdentifer : public Identifer
{
public:
  FeatureIdentifer(int labelNum)
  {
    
  }
private:
  IMat _mat;
};

}  //----end of namespace gezi

#endif  //----end of FEATURE_IDENTIFER_H_
