/**
 *  ==============================================================================
 *
 *          \file   tieba/feature/UserInfoExtractor.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-09 11:44:45.511761
 *
 *  \Description:   ���û�������Ϣ��ȡ�Ļ����û��������� 
										ע��ʱ��
										ϲ���İ���Ϣ
										�û�����Ϣ
										��ʷ��������Ϣ

										@TODO���������ھ�������û����� ���� UserInfoExExtractor
 *  ==============================================================================
 */

#ifndef TIEBA_FEATURE__USER_INFO_EXTRACTOR_H_
#define TIEBA_FEATURE__USER_INFO_EXTRACTOR_H_

#include "common_util.h"
#include "feature/Features.h"
#include "tieba/info_def.h"
#include "tieba/urate/urate_info.h"
#include "tieba/tieba_util.h"
#include "tools/uname_util.h"
namespace gezi {
	namespace tieba {

		class UserInfoExtractor : public FeaturesExtractor
		{
		public:
			UserInfoExtractor(UrateInfo& urateInfo)
				:FeaturesExtractor("UserInfo"), _urateInfo(urateInfo)
			{

			}

			virtual void extract() override
			{
				UserInfo& userInfo = _urateInfo.userInfo;
				bool isUserInfoValid = userInfo.userId != 0;
				add(isUserInfoValid, "IsUserInfoValid");
				UserPostsInfo& postsInfo = _urateInfo.postsInfo;
				bool isPostsInfoValid = postsInfo.userId != 0;
				add(isPostsInfoValid, "IsPostsInfoValid");
				{ //��ע ��˿��Ŀ
					int followCount = userInfo.followCount;
					int followedCount = userInfo.followedCount;
					add(followCount, "FollowCount");
					add(followedCount, "FollowedCount");
					double followFollowedRatio = (followCount + 1) / (double)(followedCount + 1);
					add(followFollowedRatio, "FollowFollowedRatio");
				}
				if (postsInfo.numPosts == 0)
				{
					THROW("No posts info");
				}
				{ //ע��ʱ����Ϣ
					double regDays = reg_days(postsInfo.times[0], userInfo.regTime);
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
				}
				uint nowFourmId = postsInfo.fids[0];

				{ //�û��İɵȼ���Ϣ
					UserLikeForumInfo& userLikeForumInfo = _urateInfo.userLikeForumInfo;
					bool isUserLikeForumInfoValid = userLikeForumInfo.userId;
					add(isUserLikeForumInfoValid, "IsUserLikeForumInfoValid");
					add(userLikeForumInfo.maxLevel, "ForumMaxLevel");
					add(userLikeForumInfo.numLikes, "ForumLikesNum");
					add(userLikeForumInfo.sumLevels, "ForumLevelsSum");
					add(userLikeForumInfo.GetLevel(nowFourmId), "NowForumLevel");
				}

				{ //�û��ķ�����ʷ��¼��Ϣ
					UserPostNumInfo& userPostNumInfo = _urateInfo.userPostNumInfo;
					bool isUserPostNumInfoValid = userPostNumInfo.userId != 0;
					add(isUserPostNumInfoValid, "IsUserPostNumInfoValid");
					add(userPostNumInfo.numGoods, "GoodPostNumHistory");
					add(userPostNumInfo.numPosts, "PostNumHistory");
					add(userPostNumInfo.numThreads, "ThreadNumHistory");
					add(userPostNumInfo.numPhotos, "PhotoNumHistory");

					//�û��ڵ�ǰ�ɵķ�����ʷ��Ϣ
					auto iter = _urateInfo.userPostNumInForum.find(nowFourmId);
					UserPostNumInfo userNowForumPostNumInfo;
					bool isUserNowForumPostNumInfoValid = true;
					if (iter == _urateInfo.userPostNumInForum.end() || (iter->second).userId == 0)
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

		private:
			UrateInfo& _urateInfo;
		};

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_FEATURE__USER_INFO_EXTRACTOR_H_
