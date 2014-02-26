/**
 *  ==============================================================================
 *
 *          \file   BinaryFastRankModel.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-02-25 19:39:22.092819
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef BINARY_FAST_RANK_MODEL_H_
#define BINARY_FAST_RANK_MODEL_H_

#include "model/Model.h"

class BinaryFastRankModel : public Model
{
public:
  virtual ~BinaryFastRankModel()
  {
  }
	BinaryFastRankModel(string modelName = "FastRank", int modelId = 0)
		: Model(modelName, modelId)
	{

	}

	virtual double Predict(Feature& feature);

protected:
private:
};

#endif  //----end of BINARY_FAST_RANK_MODEL_H_
