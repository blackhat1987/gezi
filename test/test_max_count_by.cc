/** 
 *  ==============================================================================
 * 
 *          \file   test_max_count_by.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-22 16:42:18.122492
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{

}

TEST(max_count_by, func)
{
		vector<uint> uids = {0, 0, 1, 1, 0 , 3, 2, 2, 3, 4, 5};
		vector<uint64> ips = {0, 0, 0, 0, 1, 0, 1, 2, 3, 1, 0};
		Pval(max_count_by(uids, ips)); //4
		Pval(min_count_by(uids, ips)); //1
		Pval(max_count_by(ips, uids)); //2./
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
