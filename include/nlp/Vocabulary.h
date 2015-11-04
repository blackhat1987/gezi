/**
 *  ==============================================================================
 *
 *          \file   nlp/Vocabulary.h
 *
 *        \author   chenghuige
 *
 *          \date   2015-10-30 13:48:30.800547
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef GEZI_NLP__VOCABULARY_H_
#define GEZI_NLP__VOCABULARY_H_
#include "Identifer.h"

namespace gezi {

class Vocabulary : public ValueIdentifer<int64>
{
public:
	int64 freq(int index) const
	{
		return _values[index];
	}

	//注意 可能 -1 越界
	int64 freq(string key) const
	{
		return _values[id(key)];
	}
protected:
private:

};

}  //----end of namespace gezi

#endif  //----end of GEZI_NLP__VOCABULARY_H_
