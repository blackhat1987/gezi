/** 
 *  ==============================================================================
 * 
 *          \file   test_get_user_posts.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-03 23:16:10.917401
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
DEFINE_int32(n, 25, "max posts num");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

//获取用户最近的发帖
TEST(get_user_posts_info, func)
{
	UserPostsInfo info = get_user_posts_info(1299045938, FLAGS_n);
	Pval2(info.userId, info.numPosts);
	for (size_t i = 0; i < info.size(); i++)
	{
		Pval5(info.fnames[i], info.titles[i], info.contents[i], info.pids[i], info.tids[i]);
	}
}

//获取用户截至到某个pid之前的帖子 输入是postId
TEST(get_user_posts_info_until, func)
{
	UserPostsInfo info = get_user_posts_info_until(57037402014, FLAGS_n);
	Pval2(info.userId, info.numPosts);
	for (size_t i = 0; i < info.size(); i++)
	{
		Pval6(to_time_str(info.times[i]), info.pids[i], info.fnames[i], info.titles[i], info.contents[i], info.tids[i]);
	}
	serialize_util::save_xml(info, "./test.data/user_posts.xml");
	{
		VLOG(0) << "Loading info from disk";
		UserPostsInfo info;
		serialize_util::load_xml("./test.data/user_posts.xml", info);
		Pval2(info.userId, info.numPosts);
		for (size_t i = 0; i < info.size(); i++)
		{
			Pval6(to_time_str(info.times[i]), info.pids[i], info.fnames[i], info.titles[i], info.contents[i], info.tids[i]);
		}
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
