/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/rsc_thread/RscThreadTextScoreExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-10-28 14:34:54.855507
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_RSC_THREAD__RSC_THREAD_TEXT_SCORE_EXTRACTOR_H_
#define TIEBA_FEATURE_RSC_THREAD__RSC_THREAD_TEXT_SCORE_EXTRACTOR_H_
#include "MLCore/PredictorFactory.h"
#include "Wrapper/SharedPredictors.h"
#include "MLCore/TextPredictor.h"
#include "tieba/tieba_util.h"
namespace gezi {
	namespace tieba {
		namespace rsc {

			class RscThreadTextScoreExtractor
			{
			public:

				RscThreadTextScoreExtractor()
				{
					Init();
				}

				string name()
				{
					return "RscThreadTextScore";
				}

				void Init()
				{
					string identiferPath0 = "./data/ltrate.thread.model/identifer.bin";
					PSCONF(identiferPath0, name());
					string identiferPath1 = "./data/rsc.model/identifer.bin";
					PSCONF(identiferPath1, name());
					_identiferPath[0] = identiferPath0;
					_identiferPath[1] = identiferPath1;

					string predictorPath0 = "./data/ltrate.thread.model";
					PSCONF(predictorPath0, name());
					string predictorPath1 = "./data/rsc.model";
					PSCONF(predictorPath1, name());
					_predictorPath[0] = predictorPath0;
					_predictorPath[1] = predictorPath1;
					//{
					//	//mutex m; //local no effect
					//	lock_guard<mutex> lk(theMutex());
					//	//int len = _isRsc ? 1 : 2;
					//	int len = 1;
					//	//通过在Init过程加锁的情况下初始化 加锁保证安全 而Init中只访问一次都 后续使用不需要加锁也比较安全
					//	//@TODO 更好的方法？ language model nlp的实现是每次都加锁吗 访问的时候 按照path
					//	for (int i = 0; i < len; i++)
					//	{
					//		GetIdentifer(i);
					//		GetPredictor(i);
					//	}
					//}
					int len = 2;
					for (int i = 0; i < len; i++)
					{
						GetIdentifer(i);
						GetPredictor(i);
					}

				}

				enum class TextPredictMode
				{
					titleContentSep,
					titleContentMerge
				};

				double Predict(string title, string content, int offset = 0, TextPredictMode mode = TextPredictMode::titleContentSep)
				{
					auto& identifer = GetIdentifer(offset);
					auto& predictor = GetPredictor(offset);
					title = get_real_title(title);
					if (content.size() > 100)
					{
						content = gbk_substr(content, 0, 100);
					}
					if (mode == TextPredictMode::titleContentSep)
					{
						return 	TextPredictor::Predict(title, content, identifer, predictor, _segType, _ngram, _sep);
					}
					else
					{ //rsc模式
						return TextPredictor::Predict(title + " " + content, identifer, predictor, _segType, _ngram, _sep);
					}
				}

				double Predict(string title, int offset = 1)
				{
					auto& identifer = GetIdentifer(offset);
					auto& predictor = GetPredictor(offset);
					title = get_real_title(title);
					return TextPredictor::Predict(title, identifer, predictor, _segType, _ngram, _sep);
				}


				//static mutex& theMutex()
				//{
				//	static mutex m;
				//	return m;
				//}

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
				bool _normalize = false; //是否对title，内容进行normalize

				string _predictorPath[2];
				string _identiferPath[2];
			};

		}  //----end of namespace rsc
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_RSC_THREAD__RSC_THREAD_TEXT_SCORE_EXTRACTOR_H_
