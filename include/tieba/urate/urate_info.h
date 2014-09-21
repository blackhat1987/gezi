/**
 *  ==============================================================================
 *
 *          \file   tieba/urate/urate_info.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-07 15:55:10.788791
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_URATE_URATE_INFO_H_
#define TIEBA_URATE_URATE_INFO_H_
#include "tieba/info_def.h"
namespace gezi {
	namespace tieba {

		//Urate初始基本数据 基本都是直接获取 唯一加入处理的是url再抽取 因为要继续调用url接口获取信息
		struct UrateInfo
		{
			uint64 postId = 0;
			PostInfo nowPostInfo; //当前帖的信息
			UserPostsInfo postsInfo; //用户发帖历史信息
			UserInfo userInfo; //用户基本属性信息
			UserLikeForumInfo userLikeForumInfo; //用户喜欢的吧属性
			UserPostNumInfo userPostNumInfo; //用户历史发帖统计信息
			map<uint, UserPostNumInfo> userPostNumInForum; //用户在特定吧内的历史发帖统计信息
			map<string, UrlInfo> urlInfoMap; //url信息  url->UrlInfo
			vector<vector<string> > urlsVec; //每个帖子中抽取的url数据

			bool IsValid()
			{
				return postId != 0 && size() > 0;
			}

			int type()
			{
				return nowPostInfo.IsThread();
			}

			size_t size()
			{
				return postsInfo.numPosts;
			}

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(postId);
				ar & BOOST_SERIALIZATION_NVP(nowPostInfo);
				ar & BOOST_SERIALIZATION_NVP(postsInfo);
				ar & BOOST_SERIALIZATION_NVP(userInfo);
				ar & BOOST_SERIALIZATION_NVP(userLikeForumInfo);
				ar & BOOST_SERIALIZATION_NVP(userPostNumInfo);
				ar & BOOST_SERIALIZATION_NVP(userPostNumInForum);
				ar & BOOST_SERIALIZATION_NVP(urlInfoMap);
				ar & BOOST_SERIALIZATION_NVP(urlsVec);
			}
		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_URATE_URATE_INFO_H_
