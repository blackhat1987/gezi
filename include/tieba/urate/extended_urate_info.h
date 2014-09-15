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
			}

			ExtendedUrateInfo(UrateInfo&& urateInfo)
				:UrateInfo(urateInfo)
			{
			}

			void Init()
			{
				SetHistorySize();
				ShrinkHistory();
				SetType();
			}

			static string name()
			{
				return "ExtendedUrateInfo";
			}

			bool IsValid()
			{
				return postId != 0 && size() > 0;
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

			void ExtractContentNoHtmls()
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
					locations = from(postsInfo.ips)
						>> select([this](uint64 ip) { return get_location(ipFinder(), ip); })
						>> to_vector();
				}
				PVEC(locations);
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
					ExtractContentNoHtmls();
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
				postsInfo.pids.resize(historySize);
				postsInfo.titles.resize(historySize);
				postsInfo.contents.resize(historySize);
				postsInfo.fids.resize(historySize);
				postsInfo.fnames.resize(historySize);
				postsInfo.ips.resize(historySize);
				postsInfo.isPostsDeleted.resize(historySize);
				postsInfo.isThreads.resize(historySize);
				postsInfo.times.resize(historySize);
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
			svec normalizedContents;
			svec normalizedCnContents;
			svec filteredContents; //在 htmlFilteredContents基础上进一步过滤后的内容
			svec normalizedFilteredContents;

			svec normalizedTitles;
			svec normalizedCnTitles;

			svec locations;

			int historySize;
		private:
			bool _type; //0回复，1主题

		public:
			static InitIpFinder()
			{
				ipFinder();
			}
			static IpFinder& ipFinder()
			{
				static thread_local IpFinder _ipFinder;
				if (!isIpFinderInited())
				{
					string ipData = "./data/qqwry.dat";
					bool ret = _ipFinder.Open(ipData);
					CHECK_EQ(ret, true);
					isIpFinderInited() = true;
				}
				return _ipFinder;
			}
			static bool& isIpFinderInited()
			{
				static thread_local bool _isIpFinderInited = false;
				return _isIpFinderInited;
			}
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
