/** 
 *  ==============================================================================
 * 
 *          \file   test_no_small_vector.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-07-20 20:49:05.819219
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include <folly/Benchmark.h>
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(with_small_vector, func)
{
	{
		string s = "1234你是谁呢456哎呦我去tomorrow i will go to 优衣库";
		string s2 = gezi::extract_gbk_dual(s);
		Pval(s2);
	}
	string s2;
	for (size_t i = 0; i < 1024; i++)
	{
		string s = "1234你是谁呢456哎呦我去tomorrow i will go to 优衣库";
		s2 = gezi::extract_gbk_dual(s);
	}
	//folly::doNotOptimizeAway(s2);
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