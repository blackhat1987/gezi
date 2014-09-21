/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/ContentSimExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 07:40:58.979025
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__CONTENT_SIM_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__CONTENT_SIM_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
#include "tieba/feature/feature_extractor_util.h"
namespace gezi {
	namespace tieba {

		//@TODO 部分帖子相似度很高 怎么区别度比较高
		class ContentSimExtractor : public UrateExtractor
		{
		public:

			ContentSimExtractor(const string& name = "ContentSim")
				: UrateExtractor(name)
			{

			}

			virtual void init()
			{
				info().ExtractHtmlFilteredContents();
				info().ExtractCnContents();
			}

			virtual void extract() override
			{//
				vector<string>& contents = info().cnContents;
				vector<string> threadIds = convert(info().postsInfo.tids);
				vector<string> forumIds = convert(info().postsInfo.fids);
				double simC1 = simF1(contents, threadIds) / contents.size();
				double simC2 = simF1(contents, forumIds) / contents.size();
				double sim3 = simF2(contents, threadIds) / contents.size();

				add(simC1, "simByThread1Mean");
				add(simC2, "simByForumMean");
				add(sim3, "simByThread2Mean");

				{
					double sim = 0;
					if (contents.size() > 1)
					{
						sim = simFunc1(contents[0], contents[1]);
					}
					add(sim, "top2ContentsSimMean");
				}
			}
		private:

			double simSum(vector<string>& newContents)
			{
				double simC1 = 0;
				double count = 0;
				for (size_t i = 1; i < newContents.size(); i++)
				{
					string s1 = newContents[i];
					string s2 = newContents[i - 1];
					vector<string> id_c1 = reg_split(s1.c_str(), "####");
					vector<string> id_c2 = reg_split(s2.c_str(), "####");
					if (id_c1.size() < 2 || id_c2.size() < 2)
					{
						continue;
					}
					string id1 = id_c1[0];
					string id2 = id_c2[0];

					double sim1 = simFunc1(id_c1[1], id_c2[1]);
					simC1 += sim1;
					count++;
				}
				return simC1;
			}

			double simF1(vector<string>& contents, vector<string>& vec)
			{

				vector<string> newContents;
				for (size_t i = 0; i < contents.size() && i < vec.size(); i++)
				{
					string newC = vec[i];
					newC += "####";
					newC += contents[i];
					newContents.push_back(newC);
				}
				double sim[3];
				sim[0] = simSum(newContents);
				std::sort(newContents.begin(), newContents.end(), strComp);
				sim[1] = simSum(newContents);
				// std::sort (newContents.begin(), newContents.end(), strComp2); 
				//  sim[2]=simSum(newContents);
				double max = sim[0];
				if (sim[1] > max)
				{
					max = sim[1];
				}
				// if(sim[2]>max){
				//   max=sim[2];
				//  }
				return max;
			}

			double simF2(vector<string>& contents, vector<string>& vec)
			{

				vector<string> newContents;
				for (size_t i = 0; i < contents.size() && i < vec.size(); i++)
				{
					string newC = vec[i];
					newC += "####";
					newC += contents[i];
					newContents.push_back(newC);
				}

				std::sort(newContents.begin(), newContents.end(), strComp2);
				double simC1 = 0;
				double count = 0;
				for (size_t i = 1; i < newContents.size(); i++)
				{
					string s1 = newContents[i];
					string s2 = newContents[i - 1];
					vector<string> id_c1 = reg_split(s1.c_str(), "####");
					vector<string> id_c2 = reg_split(s2.c_str(), "####");
					if (id_c1.size() < 2 || id_c2.size() < 2)
					{
						continue;
					}
					string id1 = id_c1[0];
					string id2 = id_c2[0];

					if (id1 == id2)
					{
						continue;
					}
					if (id_c2[1].size() < 15)
					{
						continue;
					}

					double sim1 = simFunc1(id_c1[1], id_c2[1]);

					if (sim1 > 0.8)
					{
						simC1++;

					}
					count++;
				}
				if (count < 10)
				{
					count = 10;
				}
				return simC1;
			}
		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__CONTENT_SIM_EXTRACTOR_H_
