/** 
 *  ==============================================================================
 * 
 *          \file   test_string_util.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-17 13:08:23.674264
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

TEST(gbk_foreach_dual, func)
{
	string s = "��ý�����2014��9��17�� good luck �ټ�";
	gbk_foreach_dual(s, [](string a) { LOG(INFO) << a; });
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
