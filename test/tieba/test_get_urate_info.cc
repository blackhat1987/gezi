/**
 *  ==============================================================================
 *
 *          \file   test_get_urate_info.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-07 16:29:37.206445
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "tieba/urate/get_urate_info.h"
#include "tieba/urate/extended_urate_info.h"
using namespace std;
using namespace gezi;
using namespace gezi::tieba;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_uint64(pid, 57037402014, "51605278519 51618140082");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(get_urate_info, func)
{
	UrateInfo info;
	{
		AutoTimer timer("GetUrateInfo");
		info = get_urate_info(FLAGS_pid);
		Pval3(info.postId, info.postsInfo.numPosts, info.postsInfo.titles[0]);
	}
	{
		AutoTimer timer("SaveXml");
		serialize::save_xml(info, "./test.data/urate_info.xml");
	}
	{
		UrateInfo info;
		serialize_util::load_xml("./test.data/urate_not_exist.xml", info);
		Pval2(info.postId, info.postsInfo.numPosts);
	}
	{
		UrateInfo info;
		serialize_util::load_xml("./test.data/urate_info.xml", info);
		Pval3(info.postId, info.postsInfo.numPosts, info.postsInfo.titles[0]);
	}
}

TEST(get_extended_urate_info, func)
{
	ExtendedUrateInfo info = get_urate_info(FLAGS_pid);
	Pval3(info.postId, info.postsInfo.numPosts, info.postsInfo.titles[0]);
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
