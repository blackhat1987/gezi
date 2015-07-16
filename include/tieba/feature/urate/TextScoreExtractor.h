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
#include "tieba/TextPredictor.h"
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

			void Init()
			{
				PVAL(name());
				string identiferPath0 = "./data/ltrate.reply.model/identifer.bin";
				PSCONF(identiferPath0, name());
				string identiferPath1 = "./data/ltrate.thread.model/identifer.bin";
				PSCONF(identiferPath1, name());
				_identiferPath[0] = identiferPath0;
				_identiferPath[1] = identiferPath1;
				PVAL(_identiferPath[0]);
				PVAL(_identiferPath[1]);

				string predictorPath0 = "./data/ltrate.reply.model";
				PSCONF(predictorPath0, name());

				string predictorPath1 = "./data/ltrate.thread.model";
				PSCONF(predictorPath1, name());
				_predictorPath[0] = predictorPath0;
				_predictorPath[1] = predictorPath1;
				PVAL(_predictorPath[0]);
				PVAL(_predictorPath[1]);
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

				PSCONF(_ngram, name());
				PSCONF(_skip, name());
				PSCONF(_sep, name());
				PSCONF(_normalize, name());
				PSCONF(_addNorm, name());
				PSCONF(_maxLen, name());
			}

			double Predict(string title, string content, int offset)
			{
				/*auto& identifer = identifers()[offset];
				auto& predictor = predictors()[offset];*/
				auto& identifer = GetIdentifer(offset);
				auto& predictor = GetPredictor(offset);
				PVAL5(name(), offset, _identiferPath[offset], identifer.size(), identifer.id("ʨ��"));
				if (!_isRsc)
				{
					return 	tieba::TextPredictor::Predict(title, content, identifer, predictor, _segType, _useMedia, _ngram, _skip, _sep);
				}
				else
				{
					return tieba::TextPredictor::Predict(title + " " + content, identifer, predictor, _segType, _ngram, _skip, _sep);
				}
			}

			double Predict(string title, string content)
			{
				int offset = _isRsc ? 0 : type();
				return Predict(title, content, offset);
			}

			virtual void extract() override
			{
				int maxTextScoreNum = 10;
				PSCONF(maxTextScoreNum, name());
				int len = std::min((int)size(), maxTextScoreNum);
				auto titles = info().postsInfo.titles;
				if (_addNorm)
				{
					for (auto& title : titles)
					{
						title = title + " " + gezi::normalize_str(title);
					}
				}
				auto contents = info().htmlFilteredContents;
				for (auto& content : contents)
				{
					if (content.size() > _maxLen)
					{
						content = gezi::gbk_substr(content, 0, _maxLen);
					}
					if (_addNorm)
					{
						content = content + " " + gezi::normalize_str(content);
					}
				}
				auto& isThreads = info().postsInfo.isThreads;
				/*dvec textScores = range(0, len) >> select([&titles, &contents](int i) { return Predict(titles[i], contents[i]); }) >> to_vector();*/
				dvec textScores;
				for (int i = 0; i < len; i++)
				{
					textScores.push_back(Predict(titles[i], contents[i]));
				}
				double textScoreMean = 0.0, textScoreVar = 1.0;
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

				double minTextScore = gezi::ufo::min(textScores, 0.0);
				double maxTextScore = gezi::ufo::max(textScores, 0.0);
				double minThreadTextScore = gezi::ufo::min(threadTextScores, 0.0);
				double maxThreadTextScore = gezi::ufo::max(threadTextScores, 0.0);
				double minReplyTextScore = gezi::ufo::min(replyTextScores, 0.0);
				double maxReplyTextScore = gezi::ufo::max(replyTextScores, 0.0);

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

				ADD_FEATURE(minTextScore);
				ADD_FEATURE(maxTextScore);
				ADD_FEATURE(minThreadTextScore);
				ADD_FEATURE(maxThreadTextScore);
				ADD_FEATURE(minReplyTextScore);
				ADD_FEATURE(maxReplyTextScore);
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
			string _sep = "\x01";
			int _segType = SEG_BASIC;
			int _maxLen = 100; //from 1024 -> 100

			bool _normalize = false; //�Ƿ��title�����ݽ���normalize
			bool _addNorm = true; // title + normalized_title, content + normalized_content

			bool _useMedia = false;

			bool _isRsc = false; //�Ƿ���rscģʽ rscģʽtitle��content������

			string _predictorPath[2];
			string _identiferPath[2];
		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__TEXT_SCORE_EXTRACTOR_H_
