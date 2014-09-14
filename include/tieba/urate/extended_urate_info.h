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
				SetType();
			}

			string name()
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
					ExtractContentNoHtmls();
					numbersVec = from(htmlFilteredContents)
						>> select([](string content) { return get_nums(content); })
						>> to_vector();
				}
				PVEC(numbersVec[0]);
			}

			void ExtractNormedNumbers()
			{
				if (normedNumbersVec.empty())
				{
					ExtractNormalizedContents();
					normedNumbersVec = from(normalizedContents)
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
					ExtractContentNoHtmls();
					normalizedContents = from(htmlFilteredContents)
						>> select([](string content) { return filter_str(boost::to_lower_copy(content)); })
						>> to_vector();
				}
				PVEC(normalizedContents);
			}

			void ExtractLocations()
			{
				if (locations.empty())
				{
					locations = from(postsInfo.ips)
						>> select([this](uint64 ip) { return get_location(ipFinder(), ip); })
						>> to_vector();
				}
			}

			static string FilterContent(string content)
			{
				int max_content_length = 1024;
				PSCONF(max_content_length, name());
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
					bool needFilterContent = true;
					PSCONF(needFilterContent, name());
					//如果c#同时 needFilterContent = false 可以避免拷贝 或者c++需要shared_ptr麻烦一些 copy吧
					filteredContents = postsInfo.contents;
					if (needFilterContent)
					{
						filteredContents = from(filteredContents)
							>> select([this](string content) { return FilterContent(content); })
							>> to_vector();
					}
				}
			}

			int Type()
			{
				return _type;
			}
		private:
			int HistorySize()
			{
				int max_post_num = 25;
				PSCONF(max_post_num, name());
				if (size() > max_post_num)
				{
					return max_post_num;
				}
				return size();
			}

			void SetHistorySize()
			{
				historySize = HistorySize();
			}

			void SetType()
			{
				_type = this->type();
			}

			void IsHis
			void ShrinkHistory()
			{
				postsInfo.pids.resize(historySize);

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
