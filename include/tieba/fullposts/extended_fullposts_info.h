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

			size_t size()
			{
				return numConsideredPosts;
			}

			int numConsideredPosts = 0;
			uint64 postId = 0;
		};
	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FULLPOSTS_EXTENDED_FULLPOSTS_INFO_H_
