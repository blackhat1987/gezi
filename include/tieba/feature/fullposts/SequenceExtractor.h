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

				//@TODO ��ǰ����Ϊ���� ֻ����¥��Ϣ�����¥����Ϊģʽ û�п��ǿ�������Ϊģʽ
				int noPic2PicCount = 0;
				int pic2UrlOrAtCount = 0;
				int secondFloor2PicOrUrlOrAt = 0;

				ThreadNode threadNode;
				//�����ⷢͼƬ Ȼ����淢url����@�ļ���
				//�����ⷢ"2l" "��l" "2¥" "��¥"
				//1¥��ͼƬ 2¥ ��ͼƬ
				threadNode.hasPic = !picsVec[0].empty();
				threadNode.hasAt = !atsVec[0].empty();
				threadNode.hasUrl = !urlsVec[0].empty();
				threadNode.isShortContent = contents[0].length() < shortContentLength;
				threadNode.hasSecondFloor = gezi::contains(contents[0], "��¥") || gezi::contains(contents[0], "2¥");
				uint louzhuUid = uids[0];
				for (size_t i = 1; i < size(); i++)
				{
					bool hasPic = !picsVec[i].empty();
					bool hasUrl = !urlsVec[i].empty();
					bool hasAt = !atsVec[i].empty();
					if (uids[i] == louzhuUid)
					{
						if (!threadNode.hasPic && hasPic)
						{
							noPic2PicCount++;
						}
						if (threadNode.hasPic && (hasUrl || hasAt))
						{
							pic2UrlOrAtCount++;
						}
						if (threadNode.hasSecondFloor && (hasUrl || hasAt || hasPic))
						{
							secondFloor2PicOrUrlOrAt++;
						}
					}
				}
				ADD_FEATURE(noPic2PicCount);
				ADD_FEATURE(pic2UrlOrAtCount);
				ADD_FEATURE(secondFloor2PicOrUrlOrAt);
				//1¥��url  �ı�����< 5������ 10���ַ�

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
			}
		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_FULLPOSTS__SEQUENCE_EXTRACTOR_H_
