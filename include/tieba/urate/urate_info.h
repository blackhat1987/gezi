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

	//Urate��ʼ�������� ��������ֱ�ӻ�ȡ Ψһ���봦�����url�ٳ�ȡ ��ΪҪ��������url�ӿڻ�ȡ��Ϣ
	struct UrateInfo
	{
		uint64 pid = 0;
		UserPostsInfo postsInfo; //�û�������ʷ��Ϣ
		UserInfo userInfo; //�û�����������Ϣ
		UserLikeForumInfo userLikeForumInfo; //�û�ϲ���İ�����
		UserPostNumInfo userPostNumInfo; //�û���ʷ����ͳ����Ϣ
		map<string, UrlInfo> urlInfoMap; //url��Ϣ  url->UrlInfo
		map<uint, UserPostNumInfo> userPostNumInForum; //�û����ض����ڵ���ʷ����ͳ����Ϣ
		vector<vector<string> > urlsVec; //ÿ�������г�ȡ��url����

		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive &ar, const unsigned int version)
		{
			ar & BOOST_SERIALIZATION_NVP(pid);
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
