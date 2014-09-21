/**
 *  ==============================================================================
 *
 *          \file   tools/LanguageModel.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-18 15:08:38.444365
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TOOLS__LANGUAGE_MODEL_H_
#define TOOLS__LANGUAGE_MODEL_H_
#include "DictCalFactory.h"
namespace gezi {

class LanguageModel 
{
public:
	LanguageModel() = default;
	LanguageModel(string path, int order = 3, int oovPunish = -10)
	{
		Init(path, order, oovPunish);
	}
	~LanguageModel()
	{
		//@TODO no resource unint now
	}
	void Init(string modelPath, int order = 3, int oovPunish = -10)
	{
		_model = &LangModel::GetModel(LangModel::CalType_SignDict, modelPath.c_str(), order,
			true, true, oovPunish, NULL);
	}

	inline double GetScore(string sentence)
	{
		int num = (sentence.size() + 1) / 3;
		return -_model->CalSentence(sentence.c_str()) / (double)num;
	}

	//输入都是中文 "你好吗"
	inline double GetScoreFromCnWords(string sententce)
	{
		svec vec = gezi::to_cnvec(sententce);
		int n = vec.size();
		if (n == 0)
		{
			return 0;
		}
		string spaceSeppedSentence = gezi::join(vec);
		return GetScore(spaceSeppedSentence);
	}
protected:
private:
	const LangModel::AbstractScoreCal* _model = NULL;
};

}  //----end of namespace gezi

#endif  //----end of TOOLS__LANGUAGE_MODEL_H_
