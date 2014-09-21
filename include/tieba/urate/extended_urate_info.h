/**
 *  ==============================================================================
 *
 *          \file   tieba/urate/extended_urate_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-10 14:00:45.162506
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_URATE_EXTENDED_URATE_INFO_H_
#define TIEBA_URATE_EXTENDED_URATE_INFO_H_

#include "tieba/urate/urate_info.h"
#include "tools/ip.h"
namespace gezi {
	namespace tieba {

		struct ExtendedUrateInfo : public UrateInfo
		{
		public:
			ExtendedUrateInfo() = default;

			ExtendedUrateInfo(const UrateInfo& urateInfo)
				:UrateInfo(urateInfo)
			{
				Init();
			}
	
			ExtendedUrateInfo(UrateInfo&& urateInfo)
				:UrateInfo(urateInfo)
			{
				Init();
			}

			void Init()
			{
				SetHistorySize();
				ShrinkHistory();
				SetType();
				bool isOnline = false;
				PSCONF(isOnline, "Global");
				if (!isOnline)
				{
					AdjustLikedForums();
				}
			}

			static string name()
			{
				return "ExtendedUrateInfo";
			}

			void ExtractUrls()
			{
				if (urlsVec.empty())
				{
					urlsVec = from(postsInfo.contents)
						>> select([](string content) { return	get_urls(strip_from(content)); })
						>> to_vector();
				}
			}

			void ExtractPics()
			{
				if (picsVec.empty())
				{
					picsVec = from(postsInfo.contents)
						>> select([](string content) { return	get_pics(content); })
						>> to_vector();
				}
			}

			void ExtractAts()
			{
				if (atsVec.empty())
				{
					atsVec = from(postsInfo.contents)
						>> select([](string content) { return get_ats(content); })
						>> to_vector();
				}
			}

			void ExtractEmails()
			{
				if (emailsVec.empty())
				{
					emailsVec = from(postsInfo.contents)
						>> select([](string content) { return get_emails(content); })
						>> to_vector();
				}
			}

			void ExtractVideos()
			{
				if (videosVec.empty())
				{
					videosVec = from(postsInfo.contents)
						>> select([](string content) { return get_videos(content); })
						>> to_vector();
				}
			}

			void ExtractNumbers()
			{
				if (numbersVec.empty())
				{
					ExtractFilteredContents();
					numbersVec = from(filteredContents)
						>> select([](string content) { return get_nums(content); })
						>> to_vector();
				}
				PVEC(numbersVec[0]);
			}

			void ExtractNormedNumbers()
			{
				if (normedNumbersVec.empty())
				{
					ExtractNormalizedFilteredContents();
					normedNumbersVec = from(normalizedFilteredContents)
						>> select([](string content) { return get_nums(content); })
						>> to_vector();
				}
				PVEC(normedNumbersVec[0]);
			}

			void ExtractHtmlFilteredContents()
			{
				if (htmlFilteredContents.empty())
				{
					htmlFilteredContents = from(postsInfo.contents)
						>> select([](string content) { return strip_html(content); })
						>> to_vector();
				}
				PVEC(postsInfo.contents);
				PVEC(htmlFilteredContents);
			}

			void ExtractGbkDualContents()
			{
				if (gbkDualContents.empty())
				{
					ExtractHtmlFilteredContents();
					gbkDualContents = from(htmlFilteredContents)
						>> select([](string content) { return extract_gbk_dual(content); })
						>> to_vector();
				}
				PVEC(gbkDualContents);
			}

			void ExtractNormalizedContents()
			{
				if (normalizedContents.empty())
				{
					ExtractFilteredContents();
					normalizedContents = from(htmlFilteredContents)
						>> select([](string content) { return filter_str(boost::to_lower_copy(content)); })
						>> to_vector();
				}
				PVEC(normalizedContents);
			}

			void ExtractCnContents()
			{
				if (cnContents.empty())
				{
					ExtractNormalizedContents();
					cnContents = from(normalizedContents)
						>> select([](string content) { return extract_chinese(content); })
						>> to_vector();
				}
				PVEC(cnContents);
			}

			void ExtractNormalizedTitles()
			{
				if (normalizedTitles.empty())
				{
					normalizedTitles = from(postsInfo.titles)
						>> select([](string title) { return filter_str(boost::to_lower_copy(title)); })
						>> to_vector();
				}
				PVEC(normalizedTitles);
			}

			void ExtractCnTitles()
			{
				if (cnTitles.empty())
				{
					cnTitles = from(normalizedTitles)
						>> select([](string  title) { return extract_chinese(title); })
						>> to_vector();
				}
				PVEC(cnTitles);
			}

			void ExtractNormalizedFilteredContents()
			{
				if (normalizedFilteredContents.empty())
				{
					ExtractFilteredContents();
					normalizedFilteredContents = from(filteredContents)
						>> select([](string content) { return filter_str(boost::to_lower_copy(content)); })
						>> to_vector();
				}
				PVEC(normalizedFilteredContents);
			}

			void ExtractLocations()
			{
				if (locations.empty())
				{
					ExtractOriginalLocations();
					locations.assign(originalLocations.begin(), originalLocations.begin() + historySize);
				}
				PVEC(locations);
			}

			void ExtractOriginalLocations()
			{
				if (originalLocations.empty())
				{
					/*originalLocations = from(originalPostsInfo.ips)
						>> select([this](uint64 ip) { return get_location(_ipFinder, ip); })
						>> to_vector();*/
					originalLocations = from(originalPostsInfo.ips)
						>> select([this](uint64 ip) { return get_location(ipFinder(), ip); })
						>> to_vector();
				}
				PVEC(originalLocations);
			}

			void ExtractThreadReplyHtmlFilteredContents()
			{
				if (threadHtmlFilteredContents.empty())
				{
					ExtractHtmlFilteredContents();
					for (int i = 0; i < historySize; i++)
					{
						if (postsInfo.isThreads[i])
						{
							threadHtmlFilteredContents.push_back(htmlFilteredContents[i]);
						}
						else
						{
							replyHtmlFilteredContents.push_back(htmlFilteredContents[i]);
						}
					}
				}
				PVEC(threadHtmlFilteredContents);
				PVEC(replyHtmlFilteredContents);
			}

			void ExtractThreadReplyNormalizedContents()
			{
				if (threadNormalizedContents.empty())
				{
					ExtractNormalizedContents();
					for (int i = 0; i < historySize; i++)
					{
						if (postsInfo.isThreads[i])
						{
							threadNormalizedContents.push_back(normalizedContents[i]);
						}
						else
						{
							replyNormalizedContents.push_back(normalizedContents[i]);
						}
					}
				}
				PVEC(threadNormalizedContents);
				PVEC(replyNormalizedContents);
			}

			void ExtractThreadReplyCnContents()
			{
				if (threadCnContents.empty())
				{
					ExtractCnContents();
					for (int i = 0; i < historySize; i++)
					{
						if (postsInfo.isThreads[i])
						{
							threadCnContents.push_back(cnContents[i]);
						}
						else
						{
							replyCnContents.push_back(cnContents[i]);
						}
					}
				}
				PVEC(threadCnContents);
				PVEC(replyCnContents);
			}

			void ExtractThreadReplyTitles()
			{
				if (threadTitles.empty())
				{
					for (int i = 0; i < historySize; i++)
					{
						if (postsInfo.isThreads[i])
						{
							threadTitles.push_back(postsInfo.titles[i]);
						}
						else
						{
							replyTitles.push_back(postsInfo.titles[i]);
						}
					}
				}
				PVEC(threadTitles);
				PVEC(replyTitles);
			}

			void ExtractThreadReplyNormalizedTitles()
			{
				if (threadNormalizedTitles.empty())
				{
					ExtractNormalizedTitles();
					for (int i = 0; i < historySize; i++)
					{
						if (postsInfo.isThreads[i])
						{
							threadNormalizedTitles.push_back(normalizedTitles[i]);
						}
						else
						{
							replyNormalizedTitles.push_back(normalizedTitles[i]);
						}
					}
				}
				PVEC(threadNormalizedTitles);
				PVEC(replyNormalizedTitles);
			}

			void ExtractThreadReplyCnTitles()
			{
				if (threadCnTitles.empty())
				{
					ExtractCnTitles();
					for (int i = 0; i < historySize; i++)
					{
						if (postsInfo.isThreads[i])
						{
							threadCnTitles.push_back(cnTitles[i]);
						}
						else
						{
							replyCnTitles.push_back(cnTitles[i]);
						}
					}
				}
				PVEC(threadCnTitles);
				PVEC(replyCnTitles);
			}

			//static 意味着后续可以迁移到其它共有位置 类似自由函数
			static string filter_content(string content, int max_content_length)
			{
				string new_content = strip_from(content);
				if (new_content.size() > max_content_length + 10)
				{
					int len = max_content_length / 2;
					if (new_content[len] < 0)
					{
						len++;
					}
					string new_content1 = gezi::gbk_substr(new_content, 0, len);
					int start = new_content.size() - len - 1;

					if (new_content[start - 1] < 0)
					{
						start--;
					}

					string new_content2 = gezi::gbk_substr(new_content, start);
					new_content = new_content1 + new_content2;
				}
				return new_content;
			}

			void ExtractFilteredContents()
			{
				if (filteredContents.empty())
				{
					ExtractHtmlFilteredContents();
					bool needFilterContent = true;
					PSCONF(needFilterContent, name());
					//如果c#同时 needFilterContent = false 可以避免拷贝 或者c++需要shared_ptr麻烦一些 copy吧
					filteredContents = htmlFilteredContents;
					if (needFilterContent)
					{
						int maxContentLength = 1024;
						PSCONF(maxContentLength, name());
						filteredContents = from(filteredContents)
							>> select([this,&maxContentLength](string content) { return filter_content(content, maxContentLength); })
							>> to_vector();
					}
				}
				PVEC(filteredContents);
			}

			int Type()
			{
				return _type;
			}

			int64 NowTime()
			{
				return postsInfo.times[0];
			}
		private:
			void SetHistorySize()
			{
				int maxPostNum = 25;
				PSCONF(maxPostNum, name());
				historySize = min((int)size(), maxPostNum);
				int historyDay = 7;
				PSCONF(historyDay, name());
				int64 startTime = NowTime() - historyDay * kOneDay;
				{
					int i = 0;
					for (; i < historySize; i++)
					{
							if (postsInfo.times[i] < startTime)
							{
								break;
							}
					}
					historySize = i;
				}
			}

			void SetType()
			{
				_type = this->type();
			}

			void ShrinkHistory()
			{
				originalPostsInfo = postsInfo;
				postsInfo.pids.resize(historySize);
				postsInfo.tids.resize(historySize);
				postsInfo.titles.resize(historySize);
				postsInfo.contents.resize(historySize);
				postsInfo.fids.resize(historySize);
				postsInfo.fnames.resize(historySize);
				postsInfo.ips.resize(historySize);
				postsInfo.isPostsDeleted.resize(historySize);
				postsInfo.isThreads.resize(historySize);
				postsInfo.times.resize(historySize);
				postsInfo.level1Names.resize(historySize);
				postsInfo.level2Names.resize(historySize);
				postsInfo.ranks.resize(historySize);
				postsInfo.hotValues.resize(historySize);
			}

			//由于空间限制线上只传递关注的前10的吧
			void AdjustLikedForums()
			{
				int maxForumNum = 10;
				PSCONF(maxForumNum, name());
				int size = std::min((size_t)maxForumNum, userLikeForumInfo.levels.size());

				auto& tmap = userLikeForumInfo.infoMap;
				auto vec = partial_sort_map(tmap, size);
				decltype(userLikeForumInfo.infoMap) newMap;
				ivec newLevels;
				svec newForumNames;
				for (size_t i = 0; i < size; i++)
				{
					newMap[vec[i].first] = vec[i].second;
					newLevels.push_back(vec[i].second.level);
					newForumNames.push_back(vec[i].second.forumName);
				}

				userLikeForumInfo.sumLevels = sum(newLevels);
				userLikeForumInfo.infoMap = move(newMap);
				userLikeForumInfo.numLikes = size;
				userLikeForumInfo.levels = move(newLevels);
				userLikeForumInfo.forumNames = move(newForumNames);
			}
		public:
			//media info per content
			vector<svec> urlsVec;
			vector<svec> picsVec;
			vector<svec> atsVec;
			vector<svec> videosVec;
			vector<svec> emailsVec;

			vector<svec> numbersVec; //这些需要多个extractor share
			vector<svec> normedNumbersVec; //从normalized 内容中抽取的number

			svec htmlFilteredContents;
			svec& GetHtmlFilteredContents()
			{
				ExtractHtmlFilteredContents();
				return htmlFilteredContents;
			}
			svec normalizedContents;
			svec cnContents;
			svec filteredContents; //在 htmlFilteredContents基础上进一步过滤后的内容
			svec normalizedFilteredContents;
			svec gbkDualContents;

			svec threadHtmlFilteredContents;
			svec threadCnContents;
			svec threadNormalizedContents;
			svec replyHtmlFilteredContents;
			svec replyCnContents;
			svec replyNormalizedContents;

			svec threadTitles;
			svec threadNormalizedTitles;
			svec threadCnTitles;
			svec replyTitles;
			svec replyNormalizedTitles;
			svec replyCnTitles;

			svec normalizedTitles;
			svec cnTitles;
		
			svec originalLocations;
			svec locations;

			int historySize;

			UserPostsInfo originalPostsInfo; 	//原始数据备份 
		private:
			bool _type; //0回复，1主题

		public:
			static InitIpFinder()
			{
				ipFinder();
			}
			//static IpFinder& ipFinder() //不使用static thread_local 每次ipfinder会被重置重新加载 ExtendedUrateInfo a = b;
			//{
			//	static thread_local IpFinder _ipFinder;
			//	static thread_local bool _isIpFinderInited = false;
			//	if (!_isIpFinderInited)
			//	{
			//		string ipDataPath = "./data/qqwry.dat";
			//		PSCONF(ipDataPath, "Global");
			//		bool ret = _ipFinder.Open(ipDataPath);
			//		CHECK_EQ(ret, true);
			//		_isIpFinderInited = true;
			//	}
			//	return _ipFinder;
			//}
			//IpFinder& _ipFinder = ipFinder();
		public:
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(UrateInfo);
			}
		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_URATE_EXTENDED_URATE_INFO_H_
