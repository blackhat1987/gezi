/**
 *  ==============================================================================
 *
 *          \file   tieba/fullposts/fullposts_features.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 22:38:14.031726
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FULLPOSTS_FULLPOSTS_FEATURES_H_
#define TIEBA_FULLPOSTS_FULLPOSTS_FEATURES_H_

#include "feature/Features.h"
#include "tieba/feature/fullposts/DingtieExtractor.h"
#include "tieba/feature/fullposts/SequenceExtractor.h"
#include "tieba/feature/fullposts/TextScoreExtractor.h"
#include "tieba/urate/urate_features.h"
#include "tieba/get_info.h"
#include "other/CachedFetcher.h"

namespace gezi {
	namespace tieba {
		inline void add_fullposts_features(FeaturesExtractorMgr& mgr)
		{
			mgr.add(new DingtieExtractor);
			mgr.add(new FPSequenceExtractor);
			mgr.add(new FPTextScoreExtractor);
			mgr.add(new FPTextScoreExtractor("FPRscTextScore", true));
			mgr.add(new FPTextScoreExtractor("FPRocTextScore"));
		}

		inline Features gen_fullposts_features(uint64 tid, int num, string historyPath, string urateHistoryPath)
		{
			Features fe;
			FullPostsInfo info = try_get_info<FullPostsInfo>(tid,
				[&](uint64 tid) { return get_full_posts_info(tid, num, 0, 1); }, historyPath);
			if (info.IsValid())
			{
				FullPostsExtractor::info() = move(info);
				FeaturesExtractorMgr mgr;
				add_fullposts_features(mgr);
				mgr.extract(fe);
				{
					UrateInfo uinfo = try_get_info<UrateInfo>(info.pids.front(), [](uint64 pid) { return get_urate_info(pid); }, urateHistoryPath);
					if (uinfo.IsValid())
					{
						UrateExtractor::info() = move(uinfo);
						FeaturesExtractorMgr mgr;
						add_urate_features(mgr);
						mgr.extract(fe);
					}
					else
					{
						fe.clear();
					}
				}
			}
			return fe;
		}

		template<typename Fetcher>
		inline Features gen_fullposts_features(uint64 tid, int num, Fetcher& fetcher)
		{
			Features fe;
			FullPostsInfo info = get_full_posts_info(tid, num, 0, 1);
			if (info.IsValid())
			{
				FullPostsExtractor::info() = move(info);
				FeaturesExtractorMgr mgr;
				add_fullposts_features(mgr);
				mgr.extract(fe);
				{
					UrateInfo uinfo = fetcher.GetValue(info.pids.front(), [](uint64 pid) { return get_urate_info(pid); });
					if (uinfo.IsValid())
					{
						UrateExtractor::info() = move(uinfo);
						FeaturesExtractorMgr mgr;
						add_urate_features(mgr);
						mgr.extract(fe);
					}
					else
					{
						fe.clear();
					}
				}
			}
			return fe;
		}
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FULLPOSTS_FULLPOSTS_FEATURES_H_
