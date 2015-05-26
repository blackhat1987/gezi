/**
 *  ==============================================================================
 *
 *          \file   FastRankTrainer.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-05-23 21:14:18.648940
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef FAST_RANK_TRAINER_H_
#define FAST_RANK_TRAINER_H_
#include "Trainer.h"

namespace gezi {

class FastRankTrainer : public Trainer
{
public:
	virtual void Name()
	{
		return   "FastRankTrainer";
	}

protected:
private:

};

}  //----end of namespace gezi

#endif  //----end of FAST_RANK_TRAINER_H_
