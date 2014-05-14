/**
*  ==============================================================================
*
*          \file   .\openmp\test.cc
*
*        \author   gezi
*
*          \date   2014-02-13 11:58:47.794000
*
*  \Description:
*
*  ==============================================================================
*/

#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;

DEFINE_string(type, "simple", "");

void work(int i)
{
#pragma omp parallel for
	for (size_t j = 0; j < 10; j++)
	{
		Pval2(i, j);
	}
}
TEST(print, func)
{
#pragma omp parallel
	{
		std::cout << "Hello World!\n";
	}
	Pval(omp_get_num_threads());
	Pval(omp_get_max_threads());
	Pval(omp_get_num_procs());

//#pragma  omp parallel for
	for (size_t i = 0; i < 5; i++)
	{
		work(i);
	}
}

int main(int argc, char *argv[])
{
	FLAGS_logtostderr = true;
	testing::InitGoogleTest(&argc, argv);
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	boost::progress_timer timer;
	return RUN_ALL_TESTS();
}
