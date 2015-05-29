/** 
 *  ==============================================================================
 * 
 *          \file   test_sort.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-05-28 17:44:14.386744
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "sort_util.h"
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(sort, func)
{
	dvec vals = { 3.5, 6.5, 3.2, 1.3, 9.8, 1.2 };
	ivec indexes;
	index_sort(vals, indexes);
	for (size_t i = 0; i < indexes.size(); i++)
	{
		Pval3(i, indexes[i], vals[indexes[i]]);
	}
}

TEST(sort_greater, func)
{
	dvec vals = { 3.5, 6.5, 3.2, 1.3, 9.8, 1.2 };
	ivec indexes;
	index_sort(vals, indexes, std::greater<double>());
	for (size_t i = 0; i < indexes.size(); i++)
	{
		Pval3(i, indexes[i], vals[indexes[i]]);
	}
}

TEST(sort_lambda, func)
{
	dvec vals = { 3.5, 6.5, 3.2, 1.3, 9.8, 1.2, -10.3 };
	ivec indexes;
	index_sort(vals, indexes, [](double l, double r) { return abs(l) > abs(r); });
	for (size_t i = 0; i < indexes.size(); i++)
	{
		Pval3(i, indexes[i], vals[indexes[i]]);
	}
}

TEST(sort_len, func)
{
	dvec vals = { 3.5, 6.5, 3.2, 1.3, 9.8, 1.2, -10.3 };
	ivec indexes;
	index_sort(vals, indexes, [](double l, double r) { return abs(l) > abs(r); }, 3);
	for (size_t i = 0; i < indexes.size(); i++)
	{
		Pval3(i, indexes[i], vals[indexes[i]]);
	}
}

TEST(sort_len2, func)
{
	dvec vals = { 3.5, 6.5, 3.2, 1.3, 9.8, 1.2, -10.3 };
	ivec indexes;
	index_sort(vals, indexes, [](double l, double r) { return abs(l) > abs(r); }, 10);
	for (size_t i = 0; i < indexes.size(); i++)
	{
		Pval3(i, indexes[i], vals[indexes[i]]);
	}
}

TEST(sort_return, func)
{
	dvec vals = { 3.5, 6.5, 3.2, 1.3, 9.8, 1.2, -10.3 };
	ivec indexes = index_sort(vals, [](double l, double r) { return abs(l) > abs(r); }, 4);
	for (size_t i = 0; i < indexes.size(); i++)
	{
		Pval3(i, indexes[i], vals[indexes[i]]);
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
