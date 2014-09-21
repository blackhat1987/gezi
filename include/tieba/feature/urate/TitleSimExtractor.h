/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/TitleSimExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 07:41:08.380713
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__TITLE_SIM_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__TITLE_SIM_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
#include "tieba/feature/feature_extractor_util.h"

namespace gezi {
namespace tieba {

	class TitleSimExtractor : public UrateExtractor
	{
	public:

		TitleSimExtractor(string name = "TitleSim")
			: UrateExtractor(name)
		{

		}

		virtual void extract() override
		{//
			vector<string>& titles = info().postsInfo.titles;
			vector<string> forumIds = convert(info().postsInfo.fids);
			vector<string> threadIds = convert(info().postsInfo.tids);

			int sameThreadC;
			set<string> ThreadCs;
			int size = 0;
			for (size_t i = 0; i < threadIds.size(); i++)
			{
				string t1 = threadIds[i];
				ThreadCs.insert(t1);
				
			}
			sameThreadC = ThreadCs.size();
		/*	if (size < FLAGS_min_posts_num)
			{
				size = FLAGS_min_posts_num;
			}*/

			int minPostsNum = 10;
			PSCONF(minPostsNum, "Global");
			if (size < minPostsNum)
			{
				size = minPostsNum;
			}
			
			{
				double sim1 = simF1(titles, threadIds) / size;
				double sim2 = simF1(titles, forumIds) / size;
				add(sim1, "simByThreadMean");
				add(sim2, "simByForumMean");
			}
			{
				double sim = 0;
				if (titles.size() > 1 && is_thread(titles[0]) && is_thread(titles[1]))
				{
					sim = simFunc1(titles[0], titles[1]);
				}
				add(sim, "top2TitleSim");
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

				if (id1 == id2)
				{
					continue;
				}
				if (id_c2[1].size() < 15)
				{
					continue;
				}

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
			double max = sim[0];
			if (sim[1] > max)
			{
				max = sim[1];
			}
			return max;
		}
	};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__TITLE_SIM_EXTRACTOR_H_
