/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/UserExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-16 16:13:48.606837
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__USER_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__USER_EXTRACTOR_H_
#include "common_util.h"
#include "feature/Features.h"
#include "tieba/info_def.h"
#include "tieba/urate/urate_info.h"
#include "tieba/tieba_util.h"
#include "tools/uname_util.h"
#include "tieba/feature/urate/UrateExtractor.h"
namespace gezi {
namespace tieba {

	//@TODO need template<typename Base> class UserPostsInfoEtractor : public Base
	class UserExtractor : public UrateExtractor
	{
	public:
		UserExtractor(bool useNowPostInfo = true,
			bool useHistoryPostNum = true,
			string name = "User")
			:UrateExtractor(name),
			_useNowPostInfo(useNowPostInfo),
			_useHistoryPostNum(useHistoryPostNum)
		{

		}

		virtual void extract() override
		{
			UserInfo& userInfo = info().userInfo;
			bool isUserInfoValid = userInfo.userId != 0;
			ADD_FEATURE(isUserInfoValid);
			PostInfo& nowPostInfo = info().nowPostInfo;
			bool isNowPostInfoValid = nowPostInfo.postId != 0;
			ADD_FEATURE(isNowPostInfoValid);

			{ //��ע ��˿��Ŀ
				int followCount = userInfo.followCount;
				int followedCount = userInfo.followedCount;
				ADD_FEATURE(followCount);
				ADD_FEATURE(followedCount);
				double followFollowedRatio = (followCount + 1) / (double)(followedCount + 1);
				ADD_FEATURE(followFollowedRatio);
			}
			{ //ע��ʱ����Ϣ
				uint64 nowTime = _useNowPostInfo && isNowPostInfoValid ? nowPostInfo.createTime : (uint64)time(NULL);
				uint64 regSpan = reg_span(nowTime, userInfo.regTime);
				ADD_FEATURE(regSpan);
				int regDays = regSpan / kOneDay;
				ADD_FEATURE(regDays);
			}
			{//�Ƿ���������Ϣ
				bool hasBirth = userInfo.birthYear != 0;
				ADD_FEATURE(hasBirth);
			}
			{ //�Ƿ����Ա���Ϣ 
				bool hasSex = userInfo.userSex != 0;
				ADD_FEATURE(hasSex);
				bool isMale = userInfo.userSex == 1;
				ADD_FEATURE(isMale);
				bool isFemale = userInfo.userSex == 2;
				ADD_FEATURE(isFemale);
			}
			{ //�Ƿ��ǹ���Ա
				bool isGroupOwner = userInfo.isGroupOwner != 0;
				ADD_FEATURE(isGroupOwner);
			}
			{ //�û�����Ϣ
				string uname = userInfo.userName;
				ivec unamePattern = name_feature(uname);
				ADD_FEATURE(unamePattern);
				{//ed Ӣ�ļ�����
					bool unameIsEnNum = is_en_num_name(unamePattern);
					ADD_FEATURE(unameIsEnNum);
				}
				//�Ƿ���qq����
				bool isQQName = is_qq_name(uname);
				ADD_FEATURE(isQQName);
			}

			uint nowFourmId = nowPostInfo.forumId;
			string nowForumName = nowPostInfo.forumName;
			{ //�û��İɵȼ���Ϣ
				UserLikeForumInfo& userLikeForumInfo = info().userLikeForumInfo;
				bool isUserLikeForumInfoValid = userLikeForumInfo.userId;
				ADD_FEATURE(isUserLikeForumInfoValid);
				add(userLikeForumInfo.maxLevel, "forumMaxLevel");
				add(userLikeForumInfo.numLikes, "forumLikesNum");
				add(userLikeForumInfo.sumLevels, "forumLevelsSum");
				if (_useNowPostInfo)
				{
					add(userLikeForumInfo.GetLevel(nowForumName), "nowForumLevel");
				}
			}

			if (_useHistoryPostNum)
			{ //�û��ķ�����ʷ��¼��Ϣ
				UserPostNumInfo& userPostNumInfo = info().userPostNumInfo;
				bool isUserPostNumInfoValid = userPostNumInfo.userId != 0;
				ADD_FEATURE(isUserPostNumInfoValid);
				add(userPostNumInfo.numGoods, "goodPostNumHistory");
				add(userPostNumInfo.numPosts, "postNumHistory");
				add(userPostNumInfo.numThreads, "threadNumHistory");
				add(userPostNumInfo.numPhotos, "photoNumHistory");

				if (_useNowPostInfo)
				{//�û��ڵ�ǰ�ɵķ�����ʷ��Ϣ
					auto iter = info().userPostNumInForum.find(nowFourmId);
					UserPostNumInfo userNowForumPostNumInfo;
					bool isUserNowForumPostNumInfoValid = true;
					if (iter == info().userPostNumInForum.end() || (iter->second).userId == 0)
					{
						isUserNowForumPostNumInfoValid = false;
					}
					else
					{
						userNowForumPostNumInfo = iter->second;
					}
					ADD_FEATURE(isUserNowForumPostNumInfoValid);
					add(userNowForumPostNumInfo.numGoods, "nowForumGoodPostNumHistory");
					add(userNowForumPostNumInfo.numPosts, "nowForumPostNumHistory");
					add(userNowForumPostNumInfo.numThreads, "nowForumThreadNumHistory");
					add(userNowForumPostNumInfo.numPhotos, "nowForumPhotoNumHistory");

					double nowForumPostRatio = (userNowForumPostNumInfo.numPosts + 1) / (double)(userPostNumInfo.numPosts + 1);
					ADD_FEATURE(nowForumPostRatio);

					double nowForumThreadRatio = (userNowForumPostNumInfo.numThreads + 1) / (double)(userPostNumInfo.numThreads + 1);
					ADD_FEATURE(nowForumThreadRatio);

					double nowForumPhotoRatio = (userNowForumPostNumInfo.numPhotos + 1) / (double)(userPostNumInfo.numPhotos + 1);
					ADD_FEATURE(nowForumPhotoRatio);
				}
			}
		}

	private:
		bool _useNowPostInfo = true;
		bool _useHistoryPostNum = true; 
	};

}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__USER_EXTRACTOR_H_
