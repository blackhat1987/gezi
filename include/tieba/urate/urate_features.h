/**
 *  ==============================================================================
 *
 *          \file   tieba/urate/urate_features.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 22:35:05.534062
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_URATE_URATE_FEATURES_H_
#define TIEBA_URATE_URATE_FEATURES_H_
#include "feature/Features.h"
#include "tieba/feature/urate/SundryExtractor.h"
#include "tieba/feature/urate/UserExtractor.h"
#include "tieba/feature/urate/MediaExtractor.h"
#include "tieba/feature/urate/NumberExtractor.h"
#include "tieba/feature/urate/IpExtractor.h"
#include "tieba/feature/urate/TimeExtractor.h"
#include "tieba/feature/urate/ForumExtractor.h"
#include "tieba/feature/urate/TextExtractor.h"
#include "tieba/feature/urate/UnusalCnExtractor.h"
#include "tieba/feature/urate/UnusalCharExtractor.h"
#include "tieba/feature/urate/TextScoreExtractor.h"
#include "tieba/feature/urate/PlsaTopicExtractor.h"
#include "tieba/feature/urate/TitleSimExtractor.h"
#include "tieba/feature/urate/ContentSimExtractor.h"
#include "tieba/feature/urate/LanguageModelExtractor.h"
#include "tieba/feature/urate/SequenceExtractor.h"
#include "tieba/feature/urate/DictMatchExtractor.h"
#include "tieba/feature/urate/ImgExtrator.h" //新增


namespace gezi {
	namespace tieba {

		inline void add_urate_features(FeaturesExtractorMgr& mgr)
		{
			mgr.add(new SundryExtractor);
			mgr.add(new UserExtractor);
			mgr.add(new MediaExtractor);
			mgr.add(new NumberExtractor);
			mgr.add(new IpExtractor);
			mgr.add(new TimeExtractor);
			mgr.add(new ForumExtractor);
			mgr.add(new TextExtractor);
			mgr.add(new UnusalCnExtractor);
			mgr.add(new UnusalCharExtractor);
			mgr.add(new TextScoreExtractor);
			mgr.add(new TextScoreExtractor("RscTextScore", true));
			mgr.add(new TextScoreExtractor("RocTextScore"));

			//mgr.add(new TextScoreExtractor("TextScore2"));
			//mgr.add(new TextScoreExtractor("RocTextScore2"));

			mgr.add(new PlsaTopicExtractor);
			mgr.add(new TitleSimExtractor);
			mgr.add(new ContentSimExtractor);
			mgr.add(new LanguageModelExtractor);
			mgr.add(new SequenceExtractor);
			mgr.add(new DictMatchExtractor);
			mgr.add(new ImgExtractor); //新增
		}

		inline Features gen_urate_features(uint64 pid, string historyPath)
		{
			Features fe;
			/*UrateInfo info = try_get_info<UrateInfo>(pid, [](uint64 pid) { return get_urate_info(pid); }, FLAGS_history);*/
			int historyNum = 25;
			PSCONF(historyNum, "Urate");
			UrateInfo info = try_get_info<UrateInfo>(pid, [&](uint64 pid) { return get_urate_info(pid, true, historyNum); }, historyPath);
			if (info.IsValid())
			{
				//VLOG(0) << "Before move";
				UrateExtractor::info() = move(info);
				//VLOG(0) << "After move";
				FeaturesExtractorMgr mgr;
				add_urate_features(mgr);
				mgr.extract(fe);
			}
			return fe;
		}

		inline Features gen_urate_features(uint64 pid, UrateInfo& info, string historyPath)
		{
			Features fe;
			/*UrateInfo info = try_get_info<UrateInfo>(pid, [](uint64 pid) { return get_urate_info(pid); }, FLAGS_history);*/
			int historyNum = 25;
			PSCONF(historyNum, "Urate");
			info = try_get_info<UrateInfo>(pid, [&](uint64 pid) { return get_urate_info(pid, true, historyNum); }, historyPath);
			if (info.IsValid())
			{
				//VLOG(0) << "Before move";
				UrateExtractor::info() = info;
				//VLOG(0) << "After move";
				FeaturesExtractorMgr mgr;
				add_urate_features(mgr);
				mgr.extract(fe);
			}
			return fe;
		}

		//添加规则豁免,根据阈值scale score
		inline void adjust(double& score, const gezi::tieba::UrateInfo& uinfo)
		{
			static int min_posts_num = 3;
			PSCONF(min_posts_num, "Urate");

			string name = uinfo.userInfo.userName.c_str();
			if (gezi::contains(name, "外交")
				|| uinfo.isWhiteTitle
				|| uinfo.size() < min_posts_num)
			{
				score = 0;
			}

			if (uinfo.nowPostInfo.IsThread())
			{
				double default_spam_thre = 0.92;
				PSCONF(default_spam_thre, "UrateThread");
				double spam_thre = 0.995;
				PSCONF(spam_thre, "UrateThread");
				score = gezi::scale_value(score, default_spam_thre, spam_thre);
			}
			else
			{
				double default_spam_thre = 0.99;
				PSCONF(default_spam_thre, "UrateReply");
				double spam_thre = 0.995;
				PSCONF(spam_thre, "UrateReply");
				score = gezi::scale_value(score, default_spam_thre, spam_thre);
			}
		}

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_URATE_URATE_FEATURES_H_
