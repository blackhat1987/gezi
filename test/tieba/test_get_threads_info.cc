/** 
 *  ==============================================================================
 * 
 *          \file   test_get_threads_info.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-04 15:44:28.204193
 *  
 *  \Description:  获取主题信息
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
DEFINE_int32(vl, 0, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{

}

TEST(get_threads_info, func)
{
	auto infos = tieba::get_threads_info(vector<uint64>({ 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 }));
	PrintVec3(infos, tid, title, content);
}

TEST(get_thread_info, func)
{
	auto info = tieba::get_thread_info(3271207055);
	Pval3(info.tid, info.title, info.content);
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
