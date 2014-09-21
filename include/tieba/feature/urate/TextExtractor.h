/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/TextExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-16 16:13:55.579247
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__TEXT_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__TEXT_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
	namespace tieba {

		class TextExtractor : public UrateExtractor
		{
		public:
			TextExtractor(string name = "Text")
				:UrateExtractor(name)
			{

			}

			virtual void init() override
			{
				info().ExtractHtmlFilteredContents();
				info().ExtractNormalizedContents();
				info().ExtractNormalizedTitles();
				info().ExtractThreadReplyHtmlFilteredContents();
				info().ExtractThreadReplyNormalizedContents();
				info().ExtractThreadReplyCnContents();
				info().ExtractThreadReplyTitles();
				info().ExtractThreadReplyNormalizedTitles();
				info().ExtractThreadReplyCnTitles();
			}

			double ExtractLengthMeanVar(svec& contents, double defaultLengthMean, string name = "")
			{
				ivec lengths = from(contents)
					>> select([](string content) { return (int)content.length(); })
					>> to_vector();
				double lengthMean = defaultLengthMean, lengthVar = 1e+10;
				ufo::mean_var(lengths, lengthMean, lengthVar);
				ADD_FEATURE_WITH_PREFIX(lengthMean, name);
				ADD_FEATURE_WITH_PREFIX(lengthVar, name);
				return lengthMean;
			}

			//@TODO 可以在 ExtractLengthMeanVar 里面 计算出 post,thread, reply的三种值 返回三个mean
			double ExtractLengthMeanVar(svec& contents, double& lengthMean, double& threadLengthMean, double& replyLengthMean,
				string name = "")
			{
				auto& isThreads = info().postsInfo.isThreads;
				ivec lengths = from(contents)
					>> select([](string content) { return (int)content.length(); })
					>> to_vector();
				double lengthVar = 1e+10;
				ufo::mean_var(lengths, lengthMean, lengthVar);

				ivec threadLengths, replyLengths;
				for (size_t i = 0; i < contents.size(); i++)
				{
					if (isThreads[i])
					{
						threadLengths.push_back(lengths[i]);
					} 
					else
					{
						replyLengths.push_back(lengths[i]);
					}
				}

				double threadLengthVar = 1e+10;
				ufo::mean_var(threadLengths, threadLengthMean, threadLengthVar);
				double replyLengthVar = 1e+10;
				ufo::mean_var(replyLengths, replyLengthMean, replyLengthVar);
				int numThreadlengths = threadLengths.size();
				int numReplyLengths = replyLengths.size();
				ADD_FEATURE_WITH_PREFIX(lengthMean, name);
				ADD_FEATURE_WITH_PREFIX(lengthVar, name);
				ADD_FEATURE_WITH_PREFIX(threadLengthMean, name);
				ADD_FEATURE_WITH_PREFIX(threadLengthVar, name);
				ADD_FEATURE_WITH_PREFIX(replyLengthMean, name);
				ADD_FEATURE_WITH_PREFIX(replyLengthVar, name);
				ADD_FEATURE_WITH_PREFIX(numThreadlengths, name);
				ADD_FEATURE_WITH_PREFIX(numReplyLengths, name);
				return lengthMean;
			}

			virtual void extract() override
			{
				auto& contents = info().htmlFilteredContents;
				double contentLengthMean = 100, threadContentLengthMean = 100, replyContentLengthMean = 60;
				ExtractLengthMeanVar(contents, contentLengthMean, 
					threadContentLengthMean, replyContentLengthMean, "Content");
				
				auto& normalizedContents = info().normalizedContents;
				double normalizedContentLengthMean = 80, threadNormalizedContentLengthMean = 80, replyNormalizedContentLengthMean = 40;
				ExtractLengthMeanVar(normalizedContents, normalizedContentLengthMean,
					threadNormalizedContentLengthMean, replyNormalizedContentLengthMean, "NormalizedContent");

				auto& cnContents = info().cnContents;
				double cnContentLengthMean = 80, threadCnContentLengthMean = 80, replyCnContentLengthMean = 40;
				ExtractLengthMeanVar(cnContents, cnContentLengthMean,
					threadCnContentLengthMean, replyCnContentLengthMean, "CnContent");


				auto& titles = info().postsInfo.titles;
				double titleLengthMean = 40, threadTitleLengthMean = 40, replyTitleLengthMean = 40;
				ExtractLengthMeanVar(titles, titleLengthMean, 
					threadTitleLengthMean, replyTitleLengthMean, "Title");

				auto& normalizedTitles = info().normalizedTitles;
				double normalizedTitleLengthMean = 30, threadNormalizedTitleLengthMean = 30, replyNormalizedTitleLengthMean = 30;
				ExtractLengthMeanVar(normalizedTitles, normalizedTitleLengthMean,
					threadNormalizedTitleLengthMean, replyNormalizedTitleLengthMean, "NormalizedTitle");

				auto& cnTitles = info().cnTitles;
				double cnTitleLengthMean = 30, threadCnTitleLengthMean = 30, replyCnTitleLengthMean = 30;
				ExtractLengthMeanVar(cnTitles, cnTitleLengthMean,
					threadCnTitleLengthMean, replyCnTitleLengthMean, "CnTitle");

				{
					double nowContentLength = contents[0].size();
					double nowNormalizedContentLength = normalizedContents[0].size();
					double nowCnContentLength = cnContents[0].size();
					double nowNormalizedContentLengthRatio = (nowNormalizedContentLength + 1) / (double)(nowContentLength + 1);
					double nowCnContentLengthRatio = (nowCnContentLength + 1) / (double)(nowContentLength + 1);

					double normalizedContentLengthRatio = (normalizedContentLengthMean + 1) / (double)(contentLengthMean + 1);
					double threadNormalizedContentLengthRatio = (threadNormalizedContentLengthMean + 1) / (double)(threadContentLengthMean + 1);
					double replyNormalizedContentLengthRatio = (replyNormalizedContentLengthMean + 1) / (double)(replyContentLengthMean + 1);

					double cnContentLengthRatio = (cnContentLengthMean + 1) / (double)(contentLengthMean + 1);
					double threadCnContentLengthRatio = (threadCnContentLengthMean + 1) / (double)(threadContentLengthMean + 1);
					double replyCnContentLengthRatio = (replyCnContentLengthMean + 1) / (double)(replyContentLengthMean + 1);

					ADD_FEATURE(nowContentLength);
					ADD_FEATURE(nowNormalizedContentLength);
					ADD_FEATURE(nowCnContentLength);
					ADD_FEATURE(nowNormalizedContentLengthRatio);
					ADD_FEATURE(nowCnContentLengthRatio);
					ADD_FEATURE(cnContentLengthRatio);
					ADD_FEATURE(threadCnContentLengthRatio);
					ADD_FEATURE(replyCnContentLengthRatio);
					ADD_FEATURE(normalizedContentLengthRatio);
					ADD_FEATURE(threadNormalizedContentLengthRatio);
					ADD_FEATURE(replyNormalizedContentLengthRatio);
				}
				{
					double nowTitleLength = titles[0].size();
					double nowNormalizedTitleLength = normalizedTitles[0].size();
					double nowCnTitleLength = cnTitles[0].size();
					double nowNormalizedTitleLengthRatio = (nowNormalizedTitleLength + 1) / (double)(nowTitleLength + 1);
					double nowCnTitleLengthRatio = (nowCnTitleLength + 1) / (double)(nowTitleLength + 1);

					double normalizedTitleLengthRatio = (normalizedTitleLengthMean + 1) / (double)(titleLengthMean + 1);
					double threadNormalizedTitleLengthRatio = (threadNormalizedTitleLengthMean + 1) / (double)(threadTitleLengthMean + 1);
					double replyNormalizedTitleLengthRatio = (replyNormalizedTitleLengthMean + 1) / (double)(replyTitleLengthMean + 1);

					double cnTitleLengthRatio = (cnTitleLengthMean + 1) / (double)(titleLengthMean + 1);
					double threadCnTitleLengthRatio = (threadCnTitleLengthMean + 1) / (double)(threadTitleLengthMean + 1);
					double replyCnTitleLengthRatio = (replyCnTitleLengthMean + 1) / (double)(replyTitleLengthMean + 1);

					ADD_FEATURE(nowTitleLength);
					ADD_FEATURE(nowNormalizedTitleLength);
					ADD_FEATURE(nowCnTitleLength);
					ADD_FEATURE(nowNormalizedTitleLengthRatio);
					ADD_FEATURE(nowCnTitleLengthRatio);
					ADD_FEATURE(cnTitleLengthRatio);
					ADD_FEATURE(threadCnTitleLengthRatio);
					ADD_FEATURE(replyCnTitleLengthRatio);
					ADD_FEATURE(normalizedTitleLengthRatio);
					ADD_FEATURE(threadNormalizedTitleLengthRatio);
					ADD_FEATURE(replyNormalizedTitleLengthRatio);
				}
			}
		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__TEXT_EXTRACTOR_H_
