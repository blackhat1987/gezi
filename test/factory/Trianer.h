/**
 *  ==============================================================================
 *
 *          \file   Trianer.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-05-23 21:17:46.161927
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TRIANER_H_
#define TRIANER_H_

namespace gezi {

class Trianer 
{
public:
	virtual void Name()
	{
		return "Trainer";
	}
protected:
private:

};

typedef shared_ptr<Trainer> TrainerPtr;
}  //----end of namespace gezi

#endif  //----end of TRIANER_H_
