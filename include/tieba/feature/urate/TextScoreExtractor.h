/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/TextScoreExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-16 16:13:59.254205
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__TEXT_SCORE_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__TEXT_SCORE_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
#include "MLCore/PredictorFactory.h"
#include "Wrapper/SharedPredictors.h"
#include "MLCore/TextPredictor.h"
#include "tieba/tieba_util.h"
namespace gezi {
namespace tieba {

class TextScoreExtractor : public UrateExtractor
{
public:
	TextScoreExtractor(string name = "TextScore", bool isRsc = false)
		:UrateExtractor(name), _isRsc(isRsc)
	{
		Init();
	}

	static mutex& theMutex()
	{
		static mutex m;
		return m;
	}
	void Init() 
	{
		string identiferPath0 = "./data/ltrate.reply.model/identifer.bin";
		PSCONF(identiferPath0, name());
		string identiferPath1 = "./data/ltrate.thread.model/identifer.bin";
		PSCONF(identiferPath1, name());
		_identiferPath[0] = identiferPath0;
		_identiferPath[1] = identiferPath1;

		string predictorPath0 = "./data/ltrate.reply.model";
		PSCONF(predictorPath0, name());
		string predictorPath1 = "./data/ltrate.thread.model";
		PSCONF(predictorPath1, name());
		_predictorPath[0] = predictorPath0;
		_predictorPath[1] = predictorPath1;
		{
			//mutex m; //local no use
			lock_guard<mutex> lk(theMutex());
			int len = 2; //����rscֻ��Ҫ1��predictor ҲҪ��ô����û�취
			//ͨ����Init���̼���������³�ʼ�� ������֤��ȫ ��Init��ֻ����һ�ζ� ����ʹ�ò���Ҫ����Ҳ�Ƚϰ�ȫ
			//@TODO ���õķ����� language model nlp��ʵ����ÿ�ζ������� ���ʵ�ʱ�� ����path
			for (int i = 0; i < len; i++)
			{
				GetIdentifer(i);
				GetPredictor(i);
			}
		}
	}

	double Predict(string title, string content, int offset)
	{
		/*auto& identifer = identifers()[offset];
		auto& predictor = predictors()[offset];*/
		auto& identifer = GetIdentifer(offset);
		auto& predictor = GetPredictor(offset);
		title = get_real_title(title);
		if (content.size() > 100)
		{
			content = gbk_substr(content, 0, 100);
		}
		if (!_isRsc)
		{
			return 	TextPredictor::Predict(title, content, identifer, predictor, _segType, _ngram, _sep);
		} 
		else
		{
			return TextPredictor::Predict(title + " " + content,
				identifer, predictor, _segType, _ngram, _sep);
		}
	}

	double Predict(string title, string content)
	{
		int offset = _isRsc ? 0 : type();
		return Predict(title, content, offset);
	}

	virtual void extract() override
	{
		int maxTextScoreNum = 8;
		PSCONF(maxTextScoreNum, name());
		int len = std::min((int)size(), maxTextScoreNum);
		auto& titles = info().postsInfo.titles;
		auto& contents = info().htmlFilteredContents;
		auto& isThreads = info().postsInfo.isThreads;
		/*dvec textScores = range(0, len) >> select([&titles, &contents](int i) { return Predict(titles[i], contents[i]); }) >> to_vector();*/
		dvec textScores;
		for (int i = 0; i < len; i++)
		{
			textScores.push_back(Predict(titles[i], contents[i]));
		}
		double textScoreMean = 0, textScoreVar = 1;
		ufo::mean_var(textScores, textScoreMean, textScoreVar);
		double nowTextScore = textScores[0];
		dvec threadTextScores, replyTextScores;
		for (int i = 0; i < len; i++)
		{
			if (isThreads[i])
			{
				threadTextScores.push_back(textScores[i]);
			} 
			else
			{
				replyTextScores.push_back(textScores[i]);
			}
		}
		int numThreadTextScores = threadTextScores.size();
		int numReplyTextScores = replyTextScores.size();
		double threadTextScoreMean = 0, threadTextScoreVar = 1;
		ufo::mean_var(threadTextScores, threadTextScoreMean, threadTextScoreVar);
		double replyTextScoreMean = 0, replyTextScoreVar = 1;
		ufo::mean_var(replyTextScores, replyTextScoreMean, replyTextScoreVar);

		ADD_FEATURE(nowTextScore);
		ADD_FEATURE(textScoreMean);
		ADD_FEATURE(textScoreVar);
		ADD_FEATURE(threadTextScoreMean);
		ADD_FEATURE(threadTextScoreVar);
		ADD_FEATURE(replyTextScoreMean);
		ADD_FEATURE(replyTextScoreVar);
		ADD_FEATURE(numThreadTextScores);
		ADD_FEATURE(numReplyTextScores);
	}
protected:
private:
	/*static array<PredictorPtr, 2>& predictors()
	{
		static array<PredictorPtr, 2> _predictors;
		if (!isPredictorsInited())
		{
			string predictorPath0 = "./data/ltrate.reply.model";
			PSCONF(predictorPath0, "TextScore");
			_predictors[0] = PredictorFactory::LoadPredictor(predictorPath0);
			string predictorPath1 = "./data/ltrate.thread.model";
			PSCONF(predictorPath1, "TextScore");
			_predictors[1] = PredictorFactory::LoadPredictor(predictorPath1);
			isPredictorsInited() = true;
		}
		
		return _predictors;
	}
	static bool& isPredictorsInited()
	{
		static bool _isPredictorsInited = false;
		return _isPredictorsInited;
	}

	static array<DoubleIdentifer, 2>& identifers()
	{
		static array<DoubleIdentifer, 2> _identifers;
		if (!isIdentifersInited())
		{
			string identiferPath0 = "./data/ltrate.reply.model/identifer.bin";
			PSCONF(identiferPath0, "TextScore");
			_identifers[0].Load(identiferPath0);
			string identiferPath1 = "./data/ltrate.thread.model/identifer.bin";
			PSCONF(identiferPath1, "TextScore");
			_identifers[1].Load(identiferPath1);
			isIdentifersInited() = true;
		}
		
		return _identifers;
	}
	static bool& isIdentifersInited()
	{
		static bool _isIdentifersInited = false;
		return _isIdentifersInited;
	}*/

	PredictorPtr& GetPredictor(int offset)
	{
		return SharedPredictors::Instance(_predictorPath[offset]);
	}

	DoubleIdentifer& GetIdentifer(int offset)
	{
		return SharedDoubleIdentifers::Instance(_identiferPath[offset]);
	}

private:
	int _ngram = 3;
	string _sep = "$#$";
	int _segType = SEG_BASIC;
	bool _normalize = false; //�Ƿ��title�����ݽ���normalize

	bool _isRsc = false; //�Ƿ���rscģʽ rscģʽtitle��content������

	string _predictorPath[2];
	string _identiferPath[2];
};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__TEXT_SCORE_EXTRACTOR_H_
