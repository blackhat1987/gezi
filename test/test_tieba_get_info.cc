/** 
 *  ==============================================================================
 * 
 *          \file   test_tieba_get_info.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-06-26 17:46:06.284084
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "tieba/get_info.h"
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 0, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void test(uint64 pid, uint64 tid)
{
	bool isPidDeleted = false;
	bool isTidDeleted = false;

	tieba::get_post_deleted_info(pid, tid, isPidDeleted, isTidDeleted);

	Pval4(pid, tid, isPidDeleted, isTidDeleted);
}

TEST(tieba_get_info, func)
{
	test(52502052176, 3118313741);
	test(52694543648, 3125961562);
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
