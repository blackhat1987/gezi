/**
 *  ==============================================================================
 *
 *          \file   tools/language_model.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-18 14:19:15.566173
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TOOLS_LANGUAGE_MODEL_H_
#define TOOLS_LANGUAGE_MODEL_H_

#include "common_util.h"
#include "DictCalFactory.h"
#include "tools/LanguageModel.h"
namespace gezi {

	//@TODO 参数 另外可以用类 AbstractScoreCal*作为内部变量封装
	inline double language_model_score(string sentence)
	{
		string modelPath = "./data/tieba.5gram.lm";
		PSCONF(modelPath, "LanguageModel");
		PVAL(modelPath);
		int order = 3;
		PSCONF(order, "LanguageModel");
		double oovPunish = -10;
		PSCONF(oovPunish, "LanguageModel");
		const LangModel::AbstractScoreCal& langModel = LangModel::GetModel(LangModel::CalType_SignDict, modelPath.c_str(), order,
			true, true, oovPunish, NULL);

		int num = (sentence.size() + 1) / 3;
		return -langModel.CalSentence(sentence.c_str()) / (double)num;
	}

	//"你 好 吗" 结果除以字的数目归一化
	inline double language_model_score(string sentence, string modelPath, int order = 3, double oovPunish = -10)
	{
		const LangModel::AbstractScoreCal& langModel = LangModel::GetModel(LangModel::CalType_SignDict, modelPath.c_str(), order,
			true, true, oovPunish, NULL);

		int num = (sentence.size() + 1) / 3;
		return -langModel.CalSentence(sentence.c_str()) / (double)num;
	}

	//输入都是中文 "你好吗"
	inline double language_model_score_cnwords(string sententce)
	{
		svec vec = gezi::to_cnvec(sententce);
		int n = vec.size();
		if (n == 0)
		{
			return 0;
		}
		string spaceSeppedSentence = gezi::join(vec);
		return language_model_score(spaceSeppedSentence);
	}

	inline double language_model_score_cnwords(string sententce, string modelPath, int order = 3, double oovPunish = -10)
	{
		svec vec = gezi::to_cnvec(sententce);
		int n = vec.size();
		if (n == 0)
		{
			return 0;
		}
		string spaceSeppedSentence = gezi::join(vec);
		return language_model_score(spaceSeppedSentence, modelPath, order, oovPunish);
	}
}  //----end of namespace gezi

#endif  //----end of TOOLS_LANGUAGE_MODEL_H_
