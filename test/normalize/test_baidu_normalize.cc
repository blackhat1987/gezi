/** 
 *  ==============================================================================
 * 
 *          \file   test_baidu_normalize.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-07-23 16:32:30.354317
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "old/ccode_converter.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(baidu_normalize, func)
{
	CCodeConverter converter;
	converter.load("./data/ccode");
	string input = "123456789ABC£¬£®£¯£¿¡²£û¡³£ý£¡£À££¡ç£¥Ü‡¡££¤¡ç£¬£¡";
	Pval(input);
	Pval(converter.normalize(input));
	string simplfied = "123456789abc,./?[{]}!@#$%³µ.$$,!";
	CHECK_EQ(converter.normalize(input), simplfied);
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
