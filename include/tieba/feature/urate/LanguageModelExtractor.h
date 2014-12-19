/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/LanguageModelExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 08:23:12.886780
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__LANGUAGE_MODEL_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__LANGUAGE_MODEL_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
#include "tools/language_model.h"
namespace gezi {
	namespace tieba {

		class LanguageModelExtractor : public UrateExtractor
		{
		public:

			LanguageModelExtractor(string name = "LanguageModel")
				: UrateExtractor(name)
			{
				//_defaultValue = 2.5;
				_defaultValue = 0; //@TODO defaultValue都增加一个binary feature
				PSCONF(_defaultValue, name);
			}
		private:
			double _defaultValue;
		public:

			double LmScore(string title)
			{
				svec vec = gezi::to_cnvec(title);
				int n = vec.size();
				if (n == 0)
				{
					return _defaultValue;
				}

				title = gezi::join(vec);
				return lmScore(title);
			}

			virtual void init() override
			{
				info().ExtractCnTitles();
				info().ExtractCnContents();
			}

			virtual void extract() override
			{ //基本可以认为分值越高 语言越不符合语言模型
				//add score for titles 
				{
					dvec titleScores = from(info().cnTitles)
					>> distinct()
					//	>> where([](string title) { return gezi::is_thread(title); })
					>> select([this](string title) { return LmScore(title); })
					>> to_vector();

					double nowTitleLmScore = titleScores[0];
					ADD_FEATURE(nowTitleLmScore);
					double titleLmScoreMean = gezi::mean(titleScores);
					ADD_FEATURE(titleLmScoreMean);
				}

				vector<string>& contents = info().cnContents;
				int max_posts_num = 10;
				PSCONF(max_posts_num, name());
				max_posts_num = std::min(max_posts_num, (int)contents.size());
				vector<vector<string> > vecs(max_posts_num);
				for (int i = 0; i < (int)max_posts_num; i++)
				{
					vecs[i] = gezi::to_cnvec(contents[i]);
				}

				vector<double> scores, lscores, rscores;
				int max_len = 100;
				PSCONF(max_len, name());
				int first_len = 10;
				PSCONF(first_len, name());
				int last_len = 10;
				PSCONF(last_len, name());

				for (auto& vec : vecs)
				{
					{
						string s = vec.size() > max_len ? gezi::join(vec.begin(), vec.begin() + max_len) : gezi::join(vec);
						scores.push_back(lmScore(s));
					}
					{
						string s = vec.size() > first_len ? gezi::join(vec.begin(), vec.begin() + first_len) : gezi::join(vec);
						lscores.push_back(lmScore(s));
					}
					{
						string s = vec.size() > last_len ? gezi::join(vec.end() - last_len, vec.end()) : gezi::join(vec);
						rscores.push_back(lmScore(s));
					}
				}

				add(scores[0], "nowLmScore");
				add(lscores[0], "nowFirstLmScore");
				add(rscores[0], "nowLastLmScore");

			
				double lmScoreMean = ufo::mean(scores, _defaultValue);
				ADD_FEATURE(lmScoreMean);

				PVEC(scores);
				PVAL2(lmScoreMean, _defaultValue);

				double firstLmScoreMean = ufo::mean(lscores, _defaultValue);
				ADD_FEATURE(firstLmScoreMean);
				double lastLmScoreMean = ufo::mean(rscores, _defaultValue);
				ADD_FEATURE(lastLmScoreMean);
			}
		private:
			//"你 好 吗" 
			double lmScore(string s)
			{
				int min_cns = 1;
				PSCONF(min_cns, name());
				if (s.length() < (min_cns * 3 - 1))
				{
					return _defaultValue;
				}

				string lm_model = "./data/tieba.5gram.lm";
				PSCONF(lm_model, name());
				PVAL(lm_model);
				int order = 3;
				PSCONF(order, name());
				double oov_punish = -10;
				PSCONF(oov_punish, name());
				const LangModel::AbstractScoreCal& langModel = LangModel::GetModel(LangModel::CalType_SignDict, lm_model.c_str(), order,
					true, true, oov_punish, NULL);

				PSCONF(oov_punish, "LanguageModel");
				int num = (s.size() + 1) / 3;
				return -langModel.CalSentence(s.c_str()) / (double)num;
			}

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__LANGUAGE_MODEL_EXTRACTOR_H_
