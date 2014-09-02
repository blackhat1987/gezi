/**
 *  ==============================================================================
 *
 *          \file   test_cached_fetcher.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-02 14:35:11.001635
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "other/CachedFetcher.h"
#include "tieba/get_parsed_info.h"

using namespace std;
using namespace gezi;
using namespace gezi::tieba;
DEFINE_int32(vl, 0, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

CachedFetcher<uint64, tieba::ThreadInfo> _threadsFetcher;

TEST(get_threads_info, func)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 };
	vector<tieba::ThreadInfo> tidInfos = tieba::get_threads_info(tids, true);
	PrintVec2(tidInfos, title, content);
}

//注意参考test_bind.cc 对于重载需要特殊处理，对于默认参数 都要强制写全
TEST(bind, func)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 };
	using FuncPtr = vector<ThreadInfo>(*)(const vector<uint64>&, bool, bool);
	auto func = bind((FuncPtr)tieba::get_threads_info, _1, true, false);
	auto tidInfos = func(tids);
	PrintVec2(tidInfos, title, content);
}

//似乎这种有重载的 用lambda最方便
TEST(lambda, func)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 };
	auto func = [](const vector<uint64>& tids) { return tieba::get_threads_info(tids, true); };
	auto tidInfos = func(tids);
	PrintVec2(tidInfos, title, content);
}

TEST(cached_fetcher, func)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283 };
	Pval(_threadsFetcher.CacheSize());
	using FuncPtr = vector<ThreadInfo>(*)(const vector<uint64>&, bool, bool);
	auto tidInfos = _threadsFetcher.GetValues(tids, bind((FuncPtr)tieba::get_threads_info, _1, true, false));
	PrintVec2(tidInfos, title, content);
	Pval(_threadsFetcher.CacheSize());
}

TEST(cached_fetcher, perf)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283 };
	Pval(_threadsFetcher.CacheSize());
	auto func = [](const vector<uint64>& tids) { return tieba::get_threads_info(tids, true); };
	auto tidInfos = _threadsFetcher.GetValues(tids, func);
	PrintVec2(tidInfos, title, content);
	Pval(_threadsFetcher.CacheSize());
}

TEST(cached_fetcher, perf2)
{
	vector<uint64> tids = { 3271207055, 3271195189, 3271162283, 3271167101, 3271241387 };
	Pval(_threadsFetcher.CacheSize());
	auto tidInfos = _threadsFetcher.GetValues(tids, [](const vector<uint64>& tids) { return tieba::get_threads_info(tids, true); });
	PrintVec2(tidInfos, title, content);
	Pval(_threadsFetcher.CacheSize());
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
