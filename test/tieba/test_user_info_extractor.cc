/** 
 *  ==============================================================================
 * 
 *          \file   test_user_info_extractor.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-09 13:30:39.884322
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "tieba/feature/urate/UserInfoExtractor.h"
#include "tieba/urate/get_urate_info.h"
using namespace std;
using namespace gezi;
using namespace gezi::tieba;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_uint64(pid, 57037402014, "");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{
	string urateFile = "./test.data/" + STR(FLAGS_pid) + ".xml";
	UrateInfo info;
	{
		AutoTimer timer("Loading info");
		serialize_util::load_xml(urateFile, info);
		Pval2(info.postId, info.postsInfo.numPosts);
		if (info.postId == 0)
		{
			AutoTimer timer("GetUrateInfo");
			info = get_urate_info(FLAGS_pid);
			Pval2(info.postId, info.postsInfo.numPosts);
			serialize_util::save_xml(info, urateFile);
		}
	}
	UrateExtractor::info() = move(info);
	FeaturesExtractorMgr mgr;
	Features fe;
	mgr.add(new UserInfoExtractor());
	mgr.extract(fe);
	Pval(fe.Str());
	debug_print(fe, std::cout);
}

TEST(user_info_extractor, func)
{
	run();
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
