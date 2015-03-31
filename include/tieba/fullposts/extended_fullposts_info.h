/**
 *  ==============================================================================
 *
 *          \file   tieba/fullposts/extended_fullposts_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 22:16:25.141226
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FULLPOSTS_EXTENDED_FULLPOSTS_INFO_H_
#define TIEBA_FULLPOSTS_EXTENDED_FULLPOSTS_INFO_H_
#include "tieba/info_def.h"
#include "tieba/feature/feature_extractor_util.h"
#include "tools/ip.h"
namespace gezi {
	namespace tieba {

		struct ExtendedFullPostsInfo : public FullPostsInfo
		{
			ExtendedFullPostsInfo() = default;

			ExtendedFullPostsInfo(const FullPostsInfo& info)
				:FullPostsInfo(info)
			{
				Init();
			}

			ExtendedFullPostsInfo(FullPostsInfo&& info)
				:FullPostsInfo(info)
			{
				Init();
			}

			void Init()
			{
				if (!IsValid())
				{
					numConsideredPosts = (int)uids.size();
					return;
				}
				postId = pids[0];
				SetSize();
				Shrink();
			}

			void SetSize()
			{
				int maxNumPosts = 10;
				PSCONF(maxNumPosts, "ExtendedFullPostsInfo");
				numConsideredPosts = std::min(maxNumPosts, (int)FullPostsInfo::size());
			}

			void Shrink()
			{
				pids.resize(numConsideredPosts);
				uids.resize(numConsideredPosts);
				ips.resize(numConsideredPosts);
				times.resize(numConsideredPosts);
				unames.resize(numConsideredPosts);
				contents.resize(numConsideredPosts);
			}

			static string name()
			{
				return "ExtendedFullPostsInfo";
			}

			size_t size()
			{
				return numConsideredPosts;
			}

		protected:
			void ExtractUrls()
			{
				if (urlsVec.empty())
				{
					urlsVec = from(contents)
						>> select([](string content) { return	get_urls(strip_from(content)); })
						>> to_vector();
				}
			}

			void ExtractPics()
			{
				if (picsVec.empty())
				{
					picsVec = from(contents)
						>> select([](string content) { return	get_pics(content); })
						>> to_vector();
				}
			}

			void ExtractAts()
			{
				if (atsVec.empty())
				{
					atsVec = from(contents)
						>> select([](string content) { return get_ats(content); })
						>> to_vector();
				}
			}

			void ExtractHtmlFilteredContents()
			{
				if (htmlFilteredContents.empty())
				{
					htmlFilteredContents = from(contents)
						>> select([](string content) { return strip_html(content); })
						>> to_vector();
				}
				PVEC(htmlFilteredContents);
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
							>> select([this, &maxContentLength](string content) { return filter_content(content, maxContentLength); })
							>> to_vector();
					}
				}
				PVEC(filteredContents);
			}

			void ExtractNormalizedContents()
			{
				if (normalizedContents.empty())
				{
					ExtractHtmlFilteredContents();
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
					locations = from(ips)
						>> select([this](uint64 ip) { return get_location(ipFinder(), ip); })
						>> to_vector();
				}
				PVEC(locations);
			}

			void ExtractTop2Ips()
			{
				if (top2Ips.empty())
				{
					top2Ips = from(ips)
						>> select([this](uint64 ip) { return get_topn_ipgroup(ip, 2); })
						>> to_vector();
				}
				PVEC(top2Ips);
			}


		public:
			int numConsideredPosts = 0;
			uint64 postId = 0;

			vector<svec> picsVec;
			vector<svec> urlsVec;
			vector<svec> atsVec;
			vector<svec> numbersVec;

			svec htmlFilteredContents;
			svec normalizedContents;
			svec filteredContents;
			svec normalizedFilteredContents;

			svec locations;
			vector<uint64> top2Ips;
		};
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FULLPOSTS_EXTENDED_FULLPOSTS_INFO_H_
