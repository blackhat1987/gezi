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

		class ExtendedUrateInfo : public UrateInfo
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
				static thread_local bool _isIpFinderInited  = false;
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
