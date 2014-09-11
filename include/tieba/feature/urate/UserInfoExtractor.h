/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/urate/UserInfoExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-11 11:48:49.699004
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE_URATE__USER_INFO_EXTRACTOR_H_
#define TIEBA_FEATURE_URATE__USER_INFO_EXTRACTOR_H_
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
		class UserInfoExtractor : public UrateExtractor
		{
		public:
			UserInfoExtractor(bool useNowPostInfo = true)
				:UrateExtractor("UserInfo"), _useNowPostInfo(useNowPostInfo)
			{

			}

			virtual void extract() override
			{
				UserInfo& userInfo = info().userInfo;
				bool isUserInfoValid = userInfo.userId != 0;
				add(isUserInfoValid, "IsUserInfoValid");
				PostInfo& nowPostInfo = info().nowPostInfo;
				bool isNowPostInfoValid = nowPostInfo.postId != 0;
				add(isNowPostInfoValid, "IsNowPostInfoValid");

				{ //��ע ��˿��Ŀ
					int followCount = userInfo.followCount;
					int followedCount = userInfo.followedCount;
					add(followCount, "FollowCount");
					add(followedCount, "FollowedCount");
					double followFollowedRatio = (followCount + 1) / (double)(followedCount + 1);
					add(followFollowedRatio, "FollowFollowedRatio");
				}
				{ //ע��ʱ����Ϣ
					uint64 nowTime = _useNowPostInfo && isNowPostInfoValid ? nowPostInfo.createTime : (uint64)time(NULL);
					uint64 regSpan = reg_span(nowTime, userInfo.regTime);
					add(regSpan, "RegisterSpan");
					int regDays = regSpan / kOneDay;
					add(regDays, "RegisterDays");
				}
				{//�Ƿ���������Ϣ
					bool hasBirth = userInfo.birthYear != 0;
					add(hasBirth, "HasBirth");
				}
				{ //�Ƿ����Ա���Ϣ 
					bool hasSex = userInfo.userSex != 0;
					add(hasSex, "HasSex");
					bool isMale = userInfo.userSex == 1;
					add(isMale, "IsMale");
					bool isFemale = userInfo.userSex == 2;
					add(isFemale, "IsFemale");
				}
				{ //�Ƿ��ǹ���Ա
					bool isGroupOwner = userInfo.isGroupOwner != 0;
					add(isGroupOwner, "IsGroupOwner");
				}
				{ //�û�����Ϣ
					string uname = userInfo.userName;
					ivec unamePattern = name_feature(uname);
					add(unamePattern, "UnamePattern");
					{//ed Ӣ�ļ�����
						bool unameIsEnNum = is_en_num_name(unamePattern);
						add(unameIsEnNum, "UnameIsEnNum");
					}
					//�Ƿ���qq����
					add(is_qq_name(uname), "IsQQName");
				}

				uint nowFourmId = nowPostInfo.forumId;

				{ //�û��İɵȼ���Ϣ
					UserLikeForumInfo& userLikeForumInfo = info().userLikeForumInfo;
					bool isUserLikeForumInfoValid = userLikeForumInfo.userId;
					add(isUserLikeForumInfoValid, "IsUserLikeForumInfoValid");
					add(userLikeForumInfo.maxLevel, "ForumMaxLevel");
					add(userLikeForumInfo.numLikes, "ForumLikesNum");
					add(userLikeForumInfo.sumLevels, "ForumLevelsSum");
					if (_useNowPostInfo)
					{
						add(userLikeForumInfo.GetLevel(nowFourmId), "NowForumLevel");
					}
				}

				{ //�û��ķ�����ʷ��¼��Ϣ
					UserPostNumInfo& userPostNumInfo = info().userPostNumInfo;
					bool isUserPostNumInfoValid = userPostNumInfo.userId != 0;
					add(isUserPostNumInfoValid, "IsUserPostNumInfoValid");
					add(userPostNumInfo.numGoods, "GoodPostNumHistory");
					add(userPostNumInfo.numPosts, "PostNumHistory");
					add(userPostNumInfo.numThreads, "ThreadNumHistory");
					add(userPostNumInfo.numPhotos, "PhotoNumHistory");

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
						add(isUserNowForumPostNumInfoValid, "IsUserNowForumPostNumInfoValid");
						add(userNowForumPostNumInfo.numGoods, "NowForumGoodPostNumHistory");
						add(userNowForumPostNumInfo.numPosts, "NowForumPostNumHistory");
						add(userNowForumPostNumInfo.numThreads, "NowForumThreadNumHistory");
						add(userNowForumPostNumInfo.numPhotos, "NowForumPhotoNumHistory");

						double nowForumPostRatio = (userNowForumPostNumInfo.numPosts + 1) / (double)(userPostNumInfo.numPosts + 1);
						add(nowForumPostRatio, "NowForumPostRatio");

						double nowForumThreadRatio = (userNowForumPostNumInfo.numThreads + 1) / (double)(userPostNumInfo.numThreads + 1);
						add(nowForumThreadRatio, "NowForumThreadRatio");

						double nowForumPhotoRatio = (userNowForumPostNumInfo.numPhotos + 1) / (double)(userPostNumInfo.numPhotos + 1);
						add(nowForumPhotoRatio, "NowForumPhotoRatio");
					}
				}
			}

		private:
			bool _useNowPostInfo = true;
		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE_URATE__USER_INFO_EXTRACTOR_H_
