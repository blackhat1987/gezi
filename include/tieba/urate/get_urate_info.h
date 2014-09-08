/**
 *  ==============================================================================
 *
 *          \file   tieba/urate/get_urate_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-07 15:55:25.345281
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_URATE_GET_URATE_INFO_H_
#define TIEBA_URATE_GET_URATE_INFO_H_
#include "tieba/urate/urate_info.h"
#include "tieba/get_parsed_info.h"
#include "tools/content_process.h"
namespace gezi {
namespace tieba {
	inline UrateInfo get_urate_info(uint64 pid, int historyNum = 25, bool needUrlInfo = true)
	{
		UrateInfo urateInfo;
		PostInfo postInfo = get_post_info(pid);
		uint uid = postInfo.uid;
		urateInfo.postsInfo = get_user_posts_info_until(postInfo);
		urateInfo.userInfo = get_user_info(uid);
		urateInfo.userLikeForumInfo = get_user_like_forum_info(uid);
		urateInfo.userPostNumInfo = get_user_post_num_info(uid);
		
		set<uint> fids(urateInfo.postsInfo.fids.begin(), urateInfo.postsInfo.fids.end());
		for (uint fid : fids)
		{
			urateInfo.userPostNumInForum[fid] = get_user_post_num_info(uid, fid);
		}
		
		if (needUrlInfo)
		{
			vector<string> urlVec;
			for (auto& content : urateInfo.postsInfo.contents)
			{
				vector<string> urls = get_urls(content);
				for (auto url : urls)
				{
					urlVec.push_back(url);
				}
				urateInfo.urlsVec.emplace_back(urls);
			}
			urateInfo.urlInfoMap = get_urls_info_map(urlVec);
		}

		urateInfo.pid = pid;
		return urateInfo;
	}
}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_URATE_GET_URATE_INFO_H_
