/**
 *  ==============================================================================
 *
 *          \file   test_get_posts_info.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-04 08:05:51.995543
 *
 *  \Description: 根据pid获取帖子信息
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
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{

}
TEST(get_post_info, func)
{
	{
		tieba::PostInfo info = tieba::get_post_info(54648048128);
		Pval5(info.pid, info.forumName, info.uname, info.title, info.content);
		Pval5(info.fid, info.tid, info.uid, info.ip, info.time);
	}
	{
	tieba::PostInfo info = tieba::get_post_info(57037402014);
	Pval5(info.pid, info.forumName, info.uname, info.title, info.content);
	Pval5(info.fid, info.tid, info.uid, info.ip, info.time);
	}
}

TEST(get_posts_info, func)
{
	auto infos = tieba::get_posts_info(vector<uint64>({ 54648048128, 54648202523 }));
	auto info = infos.back();
	Pval5(info.pid, info.forumName, info.uname, info.title, info.content);
	Pval5(info.fid, info.tid, info.uid, info.ip, info.time);
	PrintVec2(infos, title, content);
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
