/** 
 *  ==============================================================================
 * 
 *          \file   test_reverse.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-08-05 11:27:22.640201
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

TEST(reverse, func)
{
	gezi::setlocale();
	//gezi::setlocale_gbk();
	Pval(wstr2str(wstr("你是谁啊a要去哪里?")));  
	wstring s = wstr("你是谁啊a要去哪里?"); 
	Pval(wstr2str(s));
	std::reverse(s.begin(), s.end());
	Pval(wstr2str(s));
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
