/** 
 *  ==============================================================================
 * 
 *          \file   test_mean_var.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-17 15:18:06.182670
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

TEST(mean_var, func)
{
	ivec vec1 = { 1, 3, 5, 2 };
	ivec vec2 = { 2, 3, 2, 3 };

	{
		double mean = 0, var = 0;
		ufo::mean_var(vec1, mean, var);
		Pval2(mean, var);
	}

	{
		double mean = 0, var = 0;
		ufo::mean_var(vec2, mean, var);
		Pval2(mean, var);
	}
}

TEST(mean_var2, func)
{
	dvec vec1 = { 1/1.0, 1/1.0, 1/1.0, 1/5.0, 1/5.0 };
	dvec vec2 = { 1/2.0, 1/2.0, 1/2.0, 1/2.0, 1/2.0 };

	{
		double mean = 0, var = 0;
		ufo::mean_var(vec1, mean, var);
		Pval2(mean, var);
	}

	{
		double mean = 0, var = 0;
		ufo::mean_var(vec2, mean, var);
		Pval2(mean, var);
	}
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
