/** 
 *  ==============================================================================
 * 
 *          \file   test_cppformat.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-10-05 22:06:42.250604
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
//#define INT INT_CPPFORMAT
//#define UINT UINT_CPPFORMAT
//#define STRING STRING_CPPFORMAT
//#include "cppformat/format.h"
//#undef INT 
//#undef UINT 
//#undef STRING 

#include <gtest/gtest.h> 
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "debug_util.h"
#include "format.h"

//#include "common_util.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{
	
}

TEST(cppformat, func)
{
	Pval(fmt::format("{0}{1}{0}", "abra", "cad"));
	VLOG(0) << fmt::format("{:s}:{:d}", "abc", 3);
	fmt::print("Hello, {}!\n", "world");  // uses Python-like format string syntax
	fmt::printf("Hello, %s!\n", "world"); // uses printf format string syntax  
	fmt::print_colored(fmt::RED, "Hello, {}!\n", "world");
	string a = "3";
	string b = "5";
	fmt::printf("%d",INT(a) + INT(b));
	Pval(fmt::format("{{{}}}", "abc"));
	Pval(fmt::format("\"{}\"", "abc"));
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
