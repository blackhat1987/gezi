/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/fullposts/TextScoreExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 22:49:57.503154
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_FULLPOSTS__TEXT_SCORE_EXTRACTOR_H_
#define TIEBA_FEATURE_FULLPOSTS__TEXT_SCORE_EXTRACTOR_H_
#include "MLCore/PredictorFactory.h"
#include "Wrapper/SharedPredictors.h"
#include "MLCore/TextPredictor.h"
#include "tieba/tieba_util.h"
#include "FullPostsExtractor.h"
namespace gezi {
	namespace tieba {
		class FPTextScoreExtractor : public FullPostsExtractor
		{
		public:
			FPTextScoreExtractor(string name = "FPTextScore", bool isRsc = false)
				:FullPostsExtractor(name), _isRsc(isRsc)
			{
				Init();
			}

			void Init()
			{
				info().ExtractHtmlFilteredContents();

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
					//mutex m; //local no effect
					lock_guard<mutex> lk(theMutex());
					int len = _isRsc ? 1 : 2;
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
					return 	TextPredictor::Predict(title, content, identifer, predictor, _segType, _useMedia, _ngram, _skip, _sep);
				}
				else
				{
					return TextPredictor::Predict(title + " " + content, identifer, predictor, _segType, _ngram, _skip, _sep);
				}
			}

			double Predict(string title, string content)
			{
				int offset = 0; //only use 0 , reply
				return Predict(title, content, offset);
			}

			virtual void extract() override
			{
				int maxTextScoreNum = 10;
				PSCONF(maxTextScoreNum, name());
				int len = std::min((int)size(), maxTextScoreNum);
				auto& contents = info().htmlFilteredContents;
				dvec textScores;
				for (int i = 1; i < len; i++)
				{
					if (info().uids[i] == info().uids[0])
					{
						textScores.push_back(Predict(info().title, contents[i]));
					}
				}
				double textScoreMean = 0.0, textScoreVar = 1.0;
				ufo::mean_var(textScores, textScoreMean, textScoreVar);
				double nowTextScore = textScores.size() > 0 ? textScores[0] : 0;
				dvec threadTextScores, replyTextScores;
				int numLouzhuReplyTextScores = textScores.size();
				double maxTextScore = ufo::max(textScores, 0.0);

				ADD_FEATURE(nowTextScore);
				ADD_FEATURE(maxTextScore);
				ADD_FEATURE(textScoreMean);
				ADD_FEATURE(textScoreVar);
				ADD_FEATURE(numLouzhuReplyTextScores);
			}
		protected:
		private:
			static mutex& theMutex()
			{
				static mutex m;
				return m;
			}

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
			int _skip = 2;
			string _sep = "$#$";
			int _segType = SEG_BASIC;
			bool _normalize = false; //�Ƿ��title�����ݽ���normalize
			bool _useMedia = false;

			bool _isRsc = false; //�Ƿ���rscģʽ rscģʽtitle��content������

			string _predictorPath[2];
			string _identiferPath[2];
		};
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_FULLPOSTS__TEXT_SCORE_EXTRACTOR_H_
