/**
 *  ==============================================================================
 *
 *          \file   test_cpplinq.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-15 07:22:20.380099
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

TEST(cpplinq, func)
{
	vector<int> vec = { 1, 2, 3 };
	auto vec2 = from(vec) >> select([](int a){return a * 2; }) >> to_vector();
	Pvec(vec2);
}

TEST(cpplinq2, func)
{
	vector<int> vec = { 1, 2, 3 };
	auto vec2 = from_iterators(vec.begin(), vec.begin() + 2) >> select([](int a){return a * 2; }) >> to_vector();
	Pvec(vec2);
}

TEST(count, func)
{
	{//bool貌似是有问题的 奇怪的是之前编译有过正常的时候。。。 vector<bool>是特殊的！
		vector<bool> vec = { 0, 1, 0, 0, 0, 1, 1 };
		//bool *pb = &vec[0];
		//Pval(*pb);
		int numThreads = from(vec) >> where([](const bool& a) { return a == true;  }) >> count();
		Pval(numThreads);
	}
	{
	vector<bool> vec = { false, true, false, false, false, true, true };
	int numThreads = from(vec) >> where([](bool a) { return a == true;  }) >> count();
	Pval(numThreads);
}
	{
		vector<bool> vec = { 0, 1, 0, 0, 0, 1, 1 };
		int numThreads = from(vec) >> sum();
		Pval(numThreads);
	}
	{
		vector<int> vec = { 0, 1, 0, 0, 0, 1, 1 };
		int numThreads = from(vec) >> sum();
		Pval(numThreads);
	}
	{
		vector<int> vec = { 0, 1, 0, 0, 0, 1, 1 };
		int numThreads = from(vec) >> where([](bool a) { return a == true;  }) >> count();
		Pval(numThreads);
	}
	{
		vector<bool> vec = { 0, 1, 0, 0, 0, 1, 1 };
		int numThreads = gezi::sum(vec);
		Pval(numThreads);
	}
	{
		vector<bool> vec = { 0, 1, 0, 0, 0, 1, 1 };
		int numThreads = gezi::sum<int>(vec);
		Pval(numThreads);
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
