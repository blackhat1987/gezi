/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/rsc_thread/RscThreadDictMatchExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-10-29 14:15:10.817466
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_RSC_THREAD__RSC_THREAD_DICT_MATCH_EXTRACTOR_H_
#define TIEBA_FEATURE_RSC_THREAD__RSC_THREAD_DICT_MATCH_EXTRACTOR_H_

#include "MatchDict.h"
#include "RegexSearcher.h"
#include "feature/features_util.h"

namespace gezi {
	namespace tieba {
		namespace rsc {

			class RscThreadDictMatchExtractor
			{
			public:
				RscThreadDictMatchExtractor()
				{
					setlocale(LC_ALL, "zh_CN.GB18030");
					string black_file = "./data/rsc.wordlist/black.dm";
					_blackDict.init(black_file);
					string black_pattern_file = "./data/rsc.wordlist/black.pattern.txt";
					_blackRegSearcher.init2(black_pattern_file);
				}

				void getBlackMatchCount(string content, Features& fe)
				{
					boost::to_lower(content);
					int count1 = _blackDict.search_count(content);
					int count2 = _blackDict.search_count(gezi::filter_str(content));

					//--------------------黑模版匹配
					if (_blackRegSearcher.has_match(str_to_wstr(content)))
					{
						count1++;
						count2++;
					}
					fe.add(count1, "BlackMatchCount");
					fe.add(count2, "NormedBlackMatchCount");
					fe.add((double)(count1 + 1) / (count2 + 1), "BlackMatchCountRatio");
				}

			private:
				gezi::MatchDict _blackDict; //因为词典不大 不使用静态方式共享
				int _maxMatchCount = 1000; //最多可能匹配的个数
				//--------------------------黑模式匹配
				RegexSearcher _blackRegSearcher;
			};

		}  //----end of namespace rsc
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_RSC_THREAD__RSC_THREAD_DICT_MATCH_EXTRACTOR_H_
