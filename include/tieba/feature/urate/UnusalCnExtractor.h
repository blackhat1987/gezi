/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/UnusalCnExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-17 14:12:21.772249
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__UNUSAL_CN_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__UNUSAL_CN_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
	namespace tieba {

		class UnusalCnExtractor : public UrateExtractor
		{
		public:
			UnusalCnExtractor(string name = "UnusalCn")
				:UrateExtractor(name)
			{

			}

			virtual void init() override
			{
				info().ExtractCnContents();
			}

			double GetCommonCnRatio(string content)
			{
				int totalCount = content.size() / 2;
				int commonCount = 0;
				gbk_dual_foreach(content, [this, &commonCount](string a) {
					if (commonCns().count(a))
					{
						commonCount++;
					};
				});
				return (1 + commonCount) / (double)(1 + totalCount);
			}

			int GetCommonCnCount(string content)
			{
				int commonCount = 0;
				gbk_dual_foreach(content, [this, &commonCount](string a) {
					if (commonCns().count(a))
					{
						commonCount++;
					}
				});
				return commonCount;
			}

			virtual void extract() override
			{
				ivec totalCountVec = from(info().cnContents) >> select([](string content) { return (int)content.length() / 2; }) >> to_vector();
				ivec commonCnCountVec = from(info().cnContents) >> select([this](string content) { return GetCommonCnCount(content); }) >> to_vector();
				int sumTotalCountVec = sum(totalCountVec);
				int sumCommonCnCountVec = sum(commonCnCountVec);

				double nowCommonCnRatio = (1 + commonCnCountVec[0]) / (double)(1 + totalCountVec[0]);
				double commonCnRatio = (1 + sumCommonCnCountVec) / (double)(1 + sumTotalCountVec);
				ADD_FEATURE(nowCommonCnRatio);
				ADD_FEATURE(commonCnRatio);
			}
		protected:
		private:
			//static set<string> ConstructCommonCns()
			//{
			//	set<string> _commonCns;
			//	string filePath = "./data/commonCns.txt";
			//	PSCONF(filePath, "UnusualCn");
			//	_commonCns = to_set(filePath);
			//	Pval(_commonCns.size());
			//	LOG_IF(WARNING, _commonCns.size() == 0) << "No common cn file loading";
			//	return _commonCns;
			//}
			static set<string>& commonCns()
			{
				//static set<string> _commonCns = ConstructCommonCns();
				static set<string> _commonCns = ([&]() { 
					set<string> _commonCns;
					string filePath = "./data/commonCns.txt";
					PSCONF(filePath, "UnusualCn");
					_commonCns = to_set(filePath);
					Pval(_commonCns.size());
					LOG_IF(WARNING, _commonCns.size() == 0) << "No common cn file loading";
					return _commonCns;
				})();
				return _commonCns;
			}
		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__UNUSAL_CN_EXTRACTOR_H_
