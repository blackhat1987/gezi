/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/MediaExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-11 14:46:46.575323
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__MEDIA_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__MEDIA_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
	namespace tieba {

		class MediaExtractor : public UrateExtractor
		{
		public:
			MediaExtractor(string name = "Media")
				:UrateExtractor(name)
			{

			}

			virtual void init() override
			{
				info().ExtractAts();
				info().ExtractEmails();
				info().ExtractPics();
				info().ExtractUrls();
				info().ExtractVideos();
			}

			void ExtractCurrentPost()
			{
				bool nowHasUrl = !info().urlsVec[0].empty();
				ADD_FEATURE(nowHasUrl);
				bool nowHasEmail = !info().emailsVec[0].empty();
				ADD_FEATURE(nowHasEmail);
				bool nowHasPic = !info().picsVec[0].empty();
				ADD_FEATURE(nowHasPic);
				bool nowHasAt = !info().atsVec[0].empty();
				ADD_FEATURE(nowHasAt);
				bool nowHasVideo = !info().atsVec[0].empty();
				ADD_FEATURE(nowHasVideo);
				double nowUrlHostRank = nowHasUrl ? _hostRanks[0] : _defaultHostRank;
				ADD_FEATURE(nowUrlHostRank);
			}

			void ExtractCount()
			{
				CHECK_NE(size(), 0) << info().postsInfo.numPosts << "\t" << info().postId;
				int numUrls = non_empty_count(info().urlsVec);
				ADD_FEATURE(numUrls);
				double numUrlsRatio = numUrls / (double)size();
				ADD_FEATURE(numUrlsRatio);
				int numEmails = non_empty_count(info().emailsVec);
				ADD_FEATURE(numEmails);
				double numEmailsRatio = numEmails / (double)size();
				int numPics = non_empty_count(info().picsVec);
				ADD_FEATURE(numPics);
				double numPicsRatio = numPics / (double)size();
				ADD_FEATURE(numPicsRatio);
				int numAts = non_empty_count(info().atsVec);
				ADD_FEATURE(numAts);
				double numAtsRatio = numAts / (double)size();
				int numVideos = non_empty_count(info().videosVec);
				ADD_FEATURE(numVideos);
				double numVideosRatio = numVideos / (double)size();
				ADD_FEATURE(numVideosRatio);

				int numMedias = 0;
				for (size_t i = 0; i < size(); i++)
				{
					if (!info().urlsVec[i].empty() || !info().atsVec[i].empty() || !info().picsVec[i].empty())
					{
						numMedias++;
					}
				}
				ADD_FEATURE(numMedias);
				double numMediasRatio = numMedias / (double)size();
				ADD_FEATURE(numMediasRatio);

				int numDistinctUrls = distinct_count_vec2d(info().urlsVec);
				int numDistinctPics = distinct_count_vec2d(info().picsVec);
				int numDistinctAts = distinct_count_vec2d(info().atsVec);
				int numDistinctEmails = distinct_count_vec2d(info().emailsVec);
				int numDistinctVedios = distinct_count_vec2d(info().videosVec);
				ADD_FEATURE(numDistinctUrls);
				ADD_FEATURE(numDistinctPics);
				ADD_FEATURE(numDistinctAts);
				ADD_FEATURE(numDistinctEmails);
				ADD_FEATURE(numDistinctVedios);

				double numDistinctUrlsRatio = numUrls == 0 ? 1 : numDistinctUrls / (double)numUrls;
				double numDistinctPicsRatio = numPics == 0 ? 1 : numDistinctPics / (double)numPics;
				double numDistinctAtsRatio = numAts == 0 ? 1 : numDistinctAts / (double)numAts;
				double numDistinctEmailsRatio = numEmails == 0 ? 1 : numDistinctEmails / (double)numEmails;
				double numDistinctVediosRatio = numVideos == 0 ? 1 : numDistinctVedios / (double)numVideos;
				ADD_FEATURE(numDistinctUrlsRatio);
				ADD_FEATURE(numDistinctPicsRatio);
				ADD_FEATURE(numDistinctAtsRatio);
				ADD_FEATURE(numDistinctEmailsRatio);
				ADD_FEATURE(numDistinctVediosRatio);
			}

			void ExtractCountInOnePost(const vector<svec>& inVec, string name)
			{
				auto countsVec = from(inVec)
					>> where([](const svec& items) { return !items.empty(); })
					>> select([](const svec& vec) { return vec.size(); })
					>> to_vector();
					double avgCountPerPost = ufo::mean(countsVec, 0.0); 
					double maxCountPerPost = ufo::max(countsVec, 0);
					double nowCount = inVec[0].size();
					ADD_FEATURE_WITH_PREFIX(avgCountPerPost, name);
					ADD_FEATURE_WITH_PREFIX(maxCountPerPost, name);
					ADD_FEATURE_WITH_PREFIX(nowCount, name);
			}

			void ExtractUrlHostRank()
			{
				_hostRanks = from(info().urlsVec)
					>> where([](const svec& urls) { return !urls.empty(); })
					>> select([this](const svec& vec) { 
					double rank = get_value(info().urlInfoMap, vec[0],
						[](const UrlInfo a) { return a.rank; }, _defaultHostRank);
				return rank < 1 ? _defaultHostRank : rank; })
					>> to_vector();
				double avgUrlHostRank = _hostRanks.empty() ? _defaultHostRank : mean(_hostRanks);
				ADD_FEATURE(avgUrlHostRank);
				double minUrlHostRank = _hostRanks.empty() ? _defaultHostRank : ufo::min(_hostRanks);
				ADD_FEATURE(minUrlHostRank);
				double maxUrlHostRank = _hostRanks.empty() ? _defaultHostRank : ufo::max(_hostRanks);
				ADD_FEATURE(maxUrlHostRank);
			}

			virtual void extract() override
			{
				ExtractCount();
				ExtractUrlHostRank();
				ExtractCurrentPost();
				ExtractCountInOnePost(info().picsVec, "Pic");
				ExtractCountInOnePost(info().atsVec, "At");
			}
		protected:
		private:
			dvec _hostRanks;
			double _defaultHostRank = 4.6; //一般4.5分以上的url 作弊率就很低了
		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__MEDIA_EXTRACTOR_H_
