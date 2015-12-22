/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/ForumExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-16 16:13:42.778163
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__FORUM_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__FORUM_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
	namespace tieba {

		class ForumExtractor : public UrateExtractor
		{
		public:
			ForumExtractor(bool isOnline = true, string name = "Forum")
				:UrateExtractor(name), _isOnline(isOnline)
			{

			}

			bool _isOnline = true;
#ifndef GCCXML
			static map<string, int>& level1Identifer()
			{
				static map<string, int> _level1Identifer = ([&](){
					map<string, int> _level1Identifer;
					string level1FilePath = "./data/level1.txt";
					PSCONF(level1FilePath, "Forum");
					_level1Identifer = gezi::to_identifer_map(level1FilePath);
					CHECK_GT(_level1Identifer.size(), 0);
					PVAL(_level1Identifer.size());
					return _level1Identifer;
				})();
				return _level1Identifer;
			}


			map<string, int>& _level1Identifer = level1Identifer();

			static map<string, double>& rankIdentifer()
			{
				static map<string, double> _rankIdentifer = ([&](){
					map<string, double> _rankIdentifer;
					string rankFilePath = "./data/forumRank.txt";
					PSCONF(rankFilePath, "Forum");
					ifstream ifs(rankFilePath);
					string line;
					while (getline(ifs, line))
					{
						string fname, rank;
						gezi::split(line, '\t', fname, rank);
						_rankIdentifer[fname] = DOUBLE(rank);
					}
					CHECK_GT(_rankIdentifer.size(), 0);
					return _rankIdentifer;
				})();
				return _rankIdentifer;
			}

			map<string, double>& _rankIdentifer = rankIdentifer();
#endif //endof ndef GCCXML
			////@TODO 合并到一起 和 levelIdentifer? 另外也可以比如是多个static 放在统一的Init函数 然后
			////利用一个Init函数内部static bool _isInited的确保构造一次 放到构造函数即可
			//static bool& isLevel1IdentiferInited()
			//{
			//	static bool _isLevel1IdentiferInited = false;
			//	return _isLevel1IdentiferInited;
			//}

			virtual void extract() override
			{
				ExtractInformation();
				ExtractRank();
				ExtractFormTitleMatch();
				ExtractLevel1Info();
			}
		protected:
		private:
			void ExtractInformation()
			{
				//吧的信息熵 度量发帖吧的不均衡性 极端的发帖最多 每个一个吧 分值是最高的 不确定性最强
				//如果信息熵很大 对应time信息 发帖时间较短 嫌疑度比较大
				auto& fids = info().postsInfo.fids;
				double fourmInfo = information(fids);
				ADD_FEATURE(fourmInfo);
				add(gezi::distinct_count(fids), "numForums");

				//一级目录信息熵
				auto level1Names = from(info().postsInfo.level1Names) >> where([](string a) { return !json_empty(a); }) >> to_vector();
				double level1Info = information(level1Names);
				ADD_FEATURE(level1Info);
				add(gezi::distinct_count(level1Names), "numLevel1Names");

			
				//二级目录信息熵
				auto level2Names = from(info().postsInfo.level2Names) >> where([](string a) { return !json_empty(a); }) >> to_vector();
				double level2Info = information(level2Names);
				ADD_FEATURE(level2Info);
				add(gezi::distinct_count(level2Names), "numLevel2Names");
			}

			void ExtractRank()
			{ //吧热度
				//auto& ranks = info().postsInfo.ranks;
				auto ranks = from(info().postsInfo.fnames) >> select([&, this](string fname) { return _rankIdentifer[fname]; }) >> to_vector();

				double rankInfo = information(ranks);
				//double rankMean = ufo::mean(ranks, 0); //知道mean的情况可以简化var的计算 但是这里不是瓶颈 简单起见
				//double rankVar = ufo::var(ranks, 1024);
				double rankMean = 0, rankVar = 1024;
				ufo::mean_var(ranks, rankMean, rankVar);
				//当前吧热度
				double nowRank = ranks.size() > 0 ? ranks[0] : 0;
				ADD_FEATURE(rankInfo);
				ADD_FEATURE(rankMean);
				ADD_FEATURE(rankVar);
				ADD_FEATURE(nowRank);
			}

			void ExtractFormTitleMatch()
			{ //TODO 更好的度量帖子和吧相关性 但是特殊处理美容类等
				auto& forumNames = info().postsInfo.fnames;
				auto& titles = info().postsInfo.titles;
				int len = std::min(forumNames.size(), titles.size());
				int titleForumMatchCount = 0;
				for (int i = 0; i < len; i++)
				{
					if (gezi::contains(titles[i], forumNames[i]))
					{
						titleForumMatchCount++;
					}
				}
				double titleForumMatchRatio = len > 0 ? titleForumMatchCount / (double)len : 0;

				ADD_FEATURE(titleForumMatchCount);
				ADD_FEATURE(titleForumMatchRatio);
			}

			void ExtractLevel1Info()
			{ //当前帖子的一级吧类目信息 
				//int len = level1Identifer().size();
				int len = _level1Identifer.size();
				vector<double> level1Vec(len + 1, 0.0);
				auto& level1Names = info().postsInfo.level1Names;
				if (level1Names.empty())
				{
					level1Vec[len] = 1.0;
				}
				else
				{
					size_t namesLen = _isOnline ? 1 : level1Names.size();
					for (size_t i = 0; i < namesLen; i++)
					{
						string level1Name = level1Names[i];
						auto iter = level1Identifer().find(level1Name);
						if (iter == level1Identifer().end())
						{
							level1Vec.back() += 1.0;
						}
						else
						{
							level1Vec[iter->second] += 1.0;
						}
					}
					for (auto& val : level1Vec)
					{
						val /= namesLen;
					}
				}
				ADD_FEATURE(level1Vec);
			}


		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__FORUM_EXTRACTOR_H_
