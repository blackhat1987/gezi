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

		inline void get_urate_info_from_uid(uint64 uid, UrateInfo& urateInfo)
		{
			urateInfo.userInfo = get_user_info(uid);
			urateInfo.userLikeForumInfo = get_user_like_forum_info(uid);
			urateInfo.userPostNumInfo = get_user_post_num_info(uid);
		}

		inline UrateInfo get_urate_info_from_uid(uint64 uid)
		{
			UrateInfo urateInfo;
			get_urate_info_from_uid(uid, urateInfo);
			return urateInfo;
		}

		inline UrateInfo get_urate_info(uint64 pid, bool needHistory = true, int historyNum = 25, bool needUrlInfo = true) 
		{
			UrateInfo urateInfo;
			PostInfo postInfo = get_post_info(pid);
			if (postInfo.postId != pid)
			{
				LOG(WARNING) << "get_post_info fail: " << pid;
				return urateInfo;
			}
			urateInfo.nowPostInfo = move(postInfo);

			uint uid = postInfo.userId;

			get_urate_info_from_uid(uid, urateInfo); 

			if (!needHistory)
			{
				urateInfo.postId = pid;
				return urateInfo;
			}

			urateInfo.postsInfo = get_user_posts_info_until(postInfo, historyNum);

			if (urateInfo.postsInfo.userId != uid)
			{ //没有帖子信息
				LOG(WARNING) << "get_user_posts_info_until fail: " << pid;
			}

			set<uint> fids(urateInfo.postsInfo.fids.begin(), urateInfo.postsInfo.fids.end());
			for (uint fid : fids)
			{
				urateInfo.userPostNumInForum[fid] = get_user_post_num_info(uid, fid);
			}

			if (needUrlInfo)
			{
				set<string> urlSet;
				for (auto& content : urateInfo.postsInfo.contents)
				{
					auto urls = get_urls(content);
					for (auto url : urls)
					{
						urlSet.insert(url);
					}
					urateInfo.urlsVec.emplace_back(urls);
				}
				urateInfo.urlInfoMap = get_urls_info_map(vector<string>(urlSet.begin(), urlSet.end()));
			}

			urateInfo.postId = pid;
			return urateInfo;
		}

		inline UrateInfo get_full_urate_info(uint64 pid, int historyNum = 25, bool needUrl = true)
		{
			return get_urate_info(pid, true, historyNum, needUrl);
		}


	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_URATE_GET_URATE_INFO_H_
