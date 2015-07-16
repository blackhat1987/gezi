/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/fullposts/SequenceExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 22:48:39.220269
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_FULLPOSTS__SEQUENCE_EXTRACTOR_H_
#define TIEBA_FEATURE_FULLPOSTS__SEQUENCE_EXTRACTOR_H_
#include "FullPostsExtractor.h"
namespace gezi {
	namespace tieba {

		class FPSequenceExtractor : public FullPostsExtractor
		{
		public:
			FPSequenceExtractor(string name = "FPSequence")
				:FullPostsExtractor(name)
			{

			}

			virtual void init() override
			{
				info().ExtractPics();
				info().ExtractUrls();
				info().ExtractAts();
				info().ExtractNormalizedFilteredContents();
			}

			struct ThreadNode
			{
				bool hasPic = false;
				bool hasAt = false;
				bool hasUrl = false;
				bool hasAny = false;
				bool isShortContent = false;
				bool hasSecondFloor = false;
			};
			virtual void extract() override
			{
				auto& urlsVec = info().urlsVec;
				auto& picsVec = info().picsVec;
				auto& atsVec = info().atsVec;
				auto& contents = info().normalizedFilteredContents;
				auto& uids = info().uids;
				int shortContentLength = 20;

				//@TODO 当前的行为序列 只考虑楼信息下面的楼主行为模式 没有考虑跨主题行为模式
				int noPic2PicCount = 0;
				int pic2UrlCount = 0, pic2AtCount = 0;
				int secondFloor2PicOrUrlOrAt = 0;

				ThreadNode threadNode;
				//先主题发图片 然后后面发url或者@的计数
				//先主题发"2l" "二l" "2楼" "二楼"
				//1楼无图片 2楼 有图片
				threadNode.hasPic = !picsVec[0].empty();
				threadNode.hasAt = !atsVec[0].empty();
				threadNode.hasUrl = !urlsVec[0].empty();
				threadNode.isShortContent = contents[0].length() < shortContentLength;
				threadNode.hasSecondFloor = gezi::contains(contents[0], "二楼") || gezi::contains(contents[0], "2楼");
				uint louzhuUid = uids[0];
				int ucount = 0;
				int numLouzhuUrls = 0, numLouzhuPics = 0, numLouzhuAts = 0;
				bool secondFloorIsUrl = false;
				for (size_t i = 1; i < size(); i++)
				{
					if (uids[i] == louzhuUid)
					{
						bool hasPic = !picsVec[i].empty();
						bool hasUrl = !urlsVec[i].empty();
						bool hasAt = !atsVec[i].empty();
						if (!threadNode.hasPic && hasPic)
						{
							noPic2PicCount++;
						}
						if (threadNode.hasPic)
						{
							if (hasUrl)
							{
								pic2UrlCount++;
							}
							if (hasAt)
							{
								pic2AtCount++;
							}
						}
						if (threadNode.hasSecondFloor && (hasUrl || hasAt || hasPic))
						{
							secondFloor2PicOrUrlOrAt++;
						}
						if (hasUrl)
						{
							numLouzhuUrls++;
							if (ucount < 3)
							{
								secondFloorIsUrl = true;
							}
						}
						if (hasPic)
						{
							numLouzhuPics++;
						}
						if (hasAt)
						{
							numLouzhuAts++;
						}
						ucount++;
						if (ucount > 10)
						{
							break;
						}
					}
				}
				ADD_FEATURE(noPic2PicCount);
				ADD_FEATURE(pic2UrlCount);
				ADD_FEATURE(pic2AtCount);
				ADD_FEATURE(secondFloor2PicOrUrlOrAt);
				ADD_FEATURE(numLouzhuAts);
				ADD_FEATURE(numLouzhuPics);
				ADD_FEATURE(numLouzhuUrls);
				ADD_FEATURE(secondFloorIsUrl);
				//1楼有url  文本内容< 5个汉字 10个字符

				int numUrlShortContents = 0;
				for (size_t i = 0; i < size(); i++)
				{
					if (uids[i] == louzhuUid)
					{
						if (!urlsVec[i].empty() && (int)contents[i].size() < shortContentLength)
						{
							numUrlShortContents++;
						}
					}
				}
				ADD_FEATURE(numUrlShortContents);

				//-----------为了回复的株连
				add(threadNode.hasPic, "hasPic");
				add(threadNode.hasAt, "hasAt");
				add(threadNode.hasUrl, "hasUrl");
				add(threadNode.hasAny, "hasAny");
				add(threadNode.isShortContent, "isShortContent");
				add(threadNode.hasSecondFloor, "hasSecondFloor");
			}
		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_FULLPOSTS__SEQUENCE_EXTRACTOR_H_
