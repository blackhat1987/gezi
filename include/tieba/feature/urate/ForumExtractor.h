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
			ForumExtractor(string name = "Forum")
				:UrateExtractor(name)
			{

			}

			static map<string, int>& level1Identifer()
			{
				static map<string, int> _level1Identifer;
				static bool _isLevel1IdentiferInited = false;
				//if (!isLevel1IdentiferInited())
				if (!_isLevel1IdentiferInited)
				{
					string level1FilePath = "./data/level1.txt";
					PSCONF(level1FilePath, "Forum");
					_level1Identifer = gezi::to_identifer_map(level1FilePath);
					CHECK_GT(_level1Identifer.size(), 0);
					PVAL(_level1Identifer.size());
					//isLevel1IdentiferInited() = true;
					_isLevel1IdentiferInited = true;
				}
				return _level1Identifer;
			}

			map<string, int>& _level1Identifer = level1Identifer();
			////@TODO �ϲ���һ�� �� levelIdentifer? ����Ҳ���Ա����Ƕ��static ����ͳһ��Init���� Ȼ��
			////����һ��Init�����ڲ�static bool _isInited��ȷ������һ�� �ŵ����캯������
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
				//�ɵ���Ϣ�� ���������ɵĲ������� ���˵ķ������ ÿ��һ���� ��ֵ����ߵ� ��ȷ������ǿ
				//�����Ϣ�غܴ� ��Ӧtime��Ϣ ����ʱ��϶� ���ɶȱȽϴ�
				auto& fids = info().postsInfo.fids;
				double fourmInfo = information(fids);
				ADD_FEATURE(fourmInfo);

				//һ��Ŀ¼��Ϣ��
				auto level1Names = from(info().postsInfo.level1Names) >> where([](string a) { return !json_empty(a); }) >> to_vector();
				double level1Info = information(level1Names);
				ADD_FEATURE(level1Info);

				//����Ŀ¼��Ϣ��
				auto level2Names = from(info().postsInfo.level2Names) >> where([](string a) { return !json_empty(a); }) >> to_vector();
				double level2Info = information(level2Names);
				ADD_FEATURE(level2Info);
			}

			void ExtractRank()
			{ //���ȶ�
				auto& ranks = info().postsInfo.ranks;
				double rankInfo = information(ranks);
				//double rankMean = ufo::mean(ranks, 0); //֪��mean��������Լ�var�ļ��� �������ﲻ��ƿ�� �����
				//double rankVar = ufo::var(ranks, 1024);
				double rankMean = 0, rankVar = 1024;
				ufo::mean_var(ranks, rankMean, rankVar);
				//��ǰ���ȶ�
				double nowRank = ranks.size() > 0 ? ranks[0] : 0;
				ADD_FEATURE(rankInfo);
				ADD_FEATURE(rankMean);
				ADD_FEATURE(rankVar);
				ADD_FEATURE(nowRank);
			}

			void ExtractFormTitleMatch()
			{ //TODO ���õĶ������ӺͰ������ �������⴦���������
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
			{ //��ǰ���ӵ�һ������Ŀ��Ϣ 
				//int len = level1Identifer().size();
				int len = _level1Identifer.size();
				vector<double> level1Vec(len + 1, 0.0);
				auto& level1Names = info().postsInfo.level1Names;
				if (level1Names.empty())
				{
					level1Vec.back() = 1.0;
				}
				else
				{
					string level1Name = level1Names[0];
					auto iter = level1Identifer().find(level1Name);
					if (iter == level1Identifer().end())
					{
						level1Vec.back() = 1.0;
					}
					else
					{
						level1Vec[iter->second] = 1.0;
					}
				}
				ADD_FEATURE(level1Vec);
			}


		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__FORUM_EXTRACTOR_H_
