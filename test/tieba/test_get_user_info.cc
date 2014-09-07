/** 
 *  ==============================================================================
 * 
 *          \file   test_get_user_info.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-05 15:03:49.715385
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "tieba/get_parsed_info.h"
using namespace std;
using namespace gezi;
using namespace gezi::tieba;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(get_user_post_num, func)
{
	UserPostNumInfo info = get_user_post_num_info(1324047674);
	Pval5(info.uid, info.numPosts, info.numThreads, info.numGoods, info.numPhotos);
	{
		info = get_user_post_num_info(1324047674, 2523743);
		Pval5(info.uid, info.numPosts, info.numThreads, info.numGoods, info.numPhotos);
	}
}

TEST(get_user_like_forum_info, func)
{
	UserLikeForumInfo info = get_user_like_forum_info(1324047674);
	Pval4(info.uid, info.numLikes, info.maxLevel, info.sumLevels);
	Pval(info.GetLevel(2523743));
	Pval(info.GetLevel(2088641));
	Pval(info.GetLevel(47));
}

TEST(get_user_info, func)
{
	gezi::tieba::UserInfo info = get_user_info(1324047674);
	Pval6(info.uid, info.uname, info.sex, info.regTime, info.followCount, info.followedCount);
	Pval5(info.uid, info.email, info.isGroupOwner, info.userTag, info.mobile);
	{
		UserInfo info = get_user_info(8219770); //"815418467"
		Pval6(info.uid, info.uname, info.sex, info.regTime, info.followCount, info.followedCount);
		Pval5(info.uid, info.email, info.isGroupOwner, info.userTag, info.mobile);
	}
	{
		UserInfo info = get_user_info(815418467); 
		Pval6(info.uid, info.uname, info.sex, info.regTime, info.followCount, info.followedCount);
		Pval5(info.uid, info.email, info.isGroupOwner, info.userTag, info.mobile);
	}
}

TEST(get_users_info, func)
{
	auto infos = get_users_info(vector<uint>({ 1324047674, 8219770, 815418467 }));
	Pval(infos.size());
	for (auto& info : infos)
	{
		Pval6(info.uid, info.uname, info.sex, info.regTime, info.followCount, info.followedCount);
		Pval5(info.uid, info.email, info.isGroupOwner, info.userTag, info.mobile);
	}
}

void run()
{
	UserPostsInfo info = get_user_posts_info(1299045938);
	Pval2(info.uid, info.numPosts);
	for (size_t i = 0; i < info.size(); i++)
	{
		Pval5(info.fnames[i], info.titles[i], info.contents[i], info.pids[i], info.tids[i]);
	}
}


int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;
	
	return RUN_ALL_TESTS();
}
