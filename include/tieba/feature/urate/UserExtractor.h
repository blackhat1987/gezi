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

#ifndef GCCXML
		static map<string, double>& nameCnFreqMap()
		{
			static map<string, double> _nameCnFreqMap = ([&](){
				map<string, double> _nameCnFreqMap;
				string nameCnFreqMapPath = "./data/nameCnFreq.txt";
				ifstream ifs(nameCnFreqMapPath);
				string line;
				double maxRank = 0;
				while (getline(ifs, line))
				{
					string cn, rank_;
					gezi::split(line, '\t', cn, rank_);
					double rank = DOUBLE(rank_);
					_nameCnFreqMap[cn] = rank;
					if (rank > maxRank)
					{
						maxRank = rank;
					}
				}
				if (!_nameCnFreqMap.empty())
				{
					_nameCnFreqMap["default"] = maxRank;
				}
				return _nameCnFreqMap;
			})();
			return _nameCnFreqMap;
		}

		map<string, double>& _nameCnFreqMap = nameCnFreqMap();
#endif

		virtual void extract() override
		{
			UserInfo& userInfo = info().userInfo;
			bool isUserInfoValid = userInfo.userId != 0;
			ADD_FEATURE(isUserInfoValid);
			PostInfo& nowPostInfo = info().nowPostInfo;
			bool isNowPostInfoValid = nowPostInfo.postId != 0;
			ADD_FEATURE(isNowPostInfoValid);

			{ //关注 粉丝数目
				int followCount = userInfo.followCount;
				int followedCount = userInfo.followedCount;
				ADD_FEATURE(followCount);
				ADD_FEATURE(followedCount);
				double followFollowedRatio = (followCount + 1) / (double)(followedCount + 1);
				ADD_FEATURE(followFollowedRatio);
			}
			{ //注册时间信息
				//uint64 nowTime = _useNowPostInfo && isNowPostInfoValid ? nowPostInfo.createTime : (uint64)time(NULL);
				uint64 nowTime = _useNowPostInfo && isNowPostInfoValid ? nowPostInfo.createTime : 0;
				uint64 regSpan = reg_span(nowTime, userInfo.regTime);
				ADD_FEATURE(regSpan);
				int regDays = regSpan / kOneDay;
				ADD_FEATURE(regDays); 
				uint64 userId = userInfo.userId;
				ADD_FEATURE(userId);
			}
			{//是否有生日信息
				bool hasBirth = userInfo.birthYear != 0;
				ADD_FEATURE(hasBirth);
			}
			{ //是否有性别信息 
				bool hasSex = userInfo.userSex != 0;
				ADD_FEATURE(hasSex);
				bool isMale = userInfo.userSex == 1;
				ADD_FEATURE(isMale);
				bool isFemale = userInfo.userSex == 2;
				ADD_FEATURE(isFemale);
			}
			{ //是否是管理员
				bool isGroupOwner = userInfo.isGroupOwner != 0;
				ADD_FEATURE(isGroupOwner);
			}
			{ //用户名信息
				string uname = userInfo.userName;
				//ivec unamePattern = name_feature(uname);
				//ADD_FEATURE(unamePattern);
				string unamePattern = simple_name_pattern(uname);
				//string patterns = "dceo";
				ivec unamePatterns = { 0, 0, 0, 0};
				for (auto item : unamePattern)
				{
					if (item == 'd')
					{
						unamePatterns[0] = 1;
					}
					else if (item == 'c')
					{
						unamePatterns[1] = 1;
					}
					else if (item == 'e')
					{
						unamePatterns[2] = 1;
					}
					else
					{
						unamePatterns[3] = 1;
					}
				}
				ADD_FEATURE(unamePatterns);
				{//ed 英文加数字
					bool unameIsEnNum = is_en_num_simple_name_pattern(unamePattern);
					ADD_FEATURE(unameIsEnNum);
				}
				//是否是qq名字
				bool isQQName = is_qq_name(uname);
				ADD_FEATURE(isQQName);

				//名字中文部分出现概率  @TODO 名字的概率模型？ 有点意思拼音输入法
				if (!_nameCnFreqMap.empty())
				{
					svec cnName = gezi::to_cnvec(gezi::extract_chinese(uname));
					double cnProb = 0;
					for (string word : cnName)
					{
						cnProb += _nameCnFreqMap.count(word) ? _nameCnFreqMap[word] : _nameCnFreqMap["default"];
					}
					cnProb = cnName.empty() ? _nameCnFreqMap["default"] : cnProb / cnName.size();
					ADD_FEATURE(cnProb);
				}
			}

			uint nowFourmId = nowPostInfo.forumId;
			string nowForumName = nowPostInfo.forumName;
			{ //用户的吧等级信息
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
			{ //用户的发帖历史记录信息
				UserPostNumInfo& userPostNumInfo = info().userPostNumInfo;
				bool isUserPostNumInfoValid = userPostNumInfo.userId != 0;
				ADD_FEATURE(isUserPostNumInfoValid);
				add(userPostNumInfo.numGoods, "goodPostNumHistory");
				add(userPostNumInfo.numPosts, "postNumHistory");
				add(userPostNumInfo.numThreads, "threadNumHistory");
				add(userPostNumInfo.numPhotos, "photoNumHistory");

				if (_useNowPostInfo)
				{//用户在当前吧的发帖历史信息
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
