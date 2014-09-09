/** 
 *  ==============================================================================
 * 
 *          \file   test_uname.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-09 10:38:26.383146
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "tieba/uname_util.h"
using namespace std;
using namespace gezi;
using namespace gezi::tieba;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{
	
}

TEST(is_qq_name, func)
{
	Pval(is_qq_name("q29109342"));
	Pval(is_qq_name("fly323254"));
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
