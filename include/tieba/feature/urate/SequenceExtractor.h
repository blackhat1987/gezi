/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/SequenceExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-14 06:19:14.229164
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__SEQUENCE_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__SEQUENCE_EXTRACTOR_H_
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
	namespace tieba {

		class SequenceExtractor : public UrateExtractor
		{
		public:
			SequenceExtractor(string name = "Sequence")
				:UrateExtractor(name)
			{

			}

			virtual void init() override
			{
				info().ExtractPics();
				info().ExtractUrls();
				info().ExtractAts();
				info().ExtractNormalizedFilteredContents();
			}

			struct Node
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
				auto& threadIds = info().postsInfo.tids;
				auto& isThreads = info().postsInfo.isThreads;
				int shortContentLength = 20;

				//@TODO ��ǰ����Ϊ���� ֻ����¥��Ϣ�����¥����Ϊģʽ û�п��ǿ�������Ϊģʽ
				int noPic2PicCount = 0;
				int pic2UrlCount = 0;
				int pic2AtCount = 0;
				int secondFloor2PicOrUrlOrAt = 0;
				//�����ⷢͼƬ Ȼ����淢url����@�ļ���
				//�����ⷢ"2l" "��l" "2¥" "��¥"
				//1¥��ͼƬ 2¥ ��ͼƬ
				{
					map<uint64, Node> userThreadsMap;
					for (int i = (int)size() - 1; i > -1; i--)
					{
						if (isThreads[i])
						{
							Node node;
							if (!picsVec[i].empty())
							{
								node.hasPic = true;
							}
							if (!atsVec[i].empty())
							{
								node.hasAt = true;
							}
							if (!urlsVec[i].empty())
							{
								node.hasUrl = true;
							}
							if (contents[i].length() < shortContentLength)
							{
								node.isShortContent = true;
							}
							if (gezi::contains(contents[i], "��¥") || gezi::contains(contents[i], "2¥"))
							{
								node.hasSecondFloor = true;
							}
							
							userThreadsMap[threadIds[i]] = node;
						}
						else
						{
							auto iter = userThreadsMap.find(threadIds[i]);
							if (iter != userThreadsMap.end())
							{
								bool hasPic = !picsVec[i].empty();
								bool hasUrl = !urlsVec[i].empty();
								bool hasAt = !atsVec[i].empty();
								Node& node = iter->second;
								if (!node.hasPic && hasPic)
								{
									noPic2PicCount++;
								}
								if (node.hasPic)
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
								if (node.hasSecondFloor && (hasUrl || hasAt || hasPic))
								{
									secondFloor2PicOrUrlOrAt++;
								}
								userThreadsMap.erase(iter);
							}
						}
					}
				}
				ADD_FEATURE(noPic2PicCount);
				ADD_FEATURE(pic2UrlCount);
				ADD_FEATURE(pic2AtCount);
				ADD_FEATURE(secondFloor2PicOrUrlOrAt);
				//1¥��url  �ı�����< 5������ 10���ַ�
				{
					vector<int> hasUrlShortContentVec(size(), 0);
					for (size_t i = 0; i < size(); i++)
					{
						if (!urlsVec[i].empty() && contents[i].size() < shortContentLength)
						{
							hasUrlShortContentVec[i] = 1;
						}
					}
					bool nowHasUrlShortContent = hasUrlShortContentVec[0];
					ADD_FEATURE(nowHasUrlShortContent);
					int sumHasUrlShortContent = gezi::sum(hasUrlShortContentVec);
					ADD_FEATURE(sumHasUrlShortContent);
				}
			}
		protected:
		private:

		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__SEQUENCE_EXTRACTOR_H_
