/**
 *  ==============================================================================
 *
 *          \file   test_get_delete_info.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-04 17:57:53.088453
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "tieba/get_parsed_info.h"
using namespace std;
using namespace gezi;
using namespace gezi::tieba;
DEFINE_int32(vl, 0, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{
	Pval(is_thread_deleted(3275090054));
	Pval(is_thread_deleted(3262970930));
	Pval(is_post_deleted(56921814305));
	Pval(is_post_deleted(56921851753));
	Pval(is_post_deleted(56921859840));

	{
		auto delInfo = get_thread_delete_info(3275090054);
		Pval3(delInfo.isDeleted, delInfo.monitorType, delInfo.opTime);
	}
	{
		auto delInfo = get_thread_delete_info(3262970930);
		Pval3(delInfo.isDeleted, delInfo.monitorType, delInfo.opTime);
	}
}

TEST(is_thread_deleted, func)
{
	Pval(is_thread_deleted(3275090054));
	Pval(is_thread_deleted(3262970930));
	Pval(is_thread_deleted(3275592070));
	Pval(is_thread_deleted(3275562780));
}

TEST(is_post_deleted, func)
{
	Pval(is_post_deleted(56934773506));
	Pval(is_post_deleted(56929671202));
	Pval(is_post_deleted(56921814305));
	Pval(is_post_deleted(56921851753));
	Pval(is_post_deleted(56921859840));
}

void show_thread_delete_info(uint64 tid)
{
	auto delInfo = get_thread_delete_info(tid);
	Pval4(tid, delInfo.isDeleted, delInfo.monitorType, delInfo.opTime);
}
TEST(get_thread_delete_info, func)
{
	show_thread_delete_info(3275090054);
	show_thread_delete_info(3262970930);
	show_thread_delete_info(3275592070);
	show_thread_delete_info(3275562780);
}

void show_post_delete_info(uint64 pid)
{
	auto delInfo = get_post_delete_info(pid);
	Pval4(pid, delInfo.isDeleted, delInfo.monitorType, delInfo.opTime);
}
TEST(get_post_delete_info, func)
{
	show_post_delete_info(56934773506);
	show_post_delete_info(56921851753);
	show_post_delete_info(56921859840);
}

TEST(is_threads_deleted, func)
{
	vector<uint64> tids = {3275090054, 3262970930, 3275592070, 3275592070, 3275562780};
	set<uint64> deletedTids = is_threads_deleted(tids);
	Prange(deletedTids.begin(), deletedTids.end());
}

TEST(is_posts_deleted, func)
{
	vector<uint64> pids = {56934773506, 56929671202, 56921814305, 56921851753, 56921859840};
	set<uint64> deletedPids = is_posts_deleted(pids);
	Prange(deletedPids.begin(), deletedPids.end());
}


TEST(get_threads_delete_info, func)
{
	vector<uint64> tids = { 3275090054, 3262970930, 3275592070, 3275592070, 3275562780 };
	auto deletedTidsInfo = get_threads_delete_info(tids);
	for (auto& item : deletedTidsInfo)
	{
		Pval3(item.first, item.second.isDeleted, item.second.monitorType);
	}
	
}

TEST(get_posts_delete_info, func)
{
	vector<uint64> pids = { 56934773506, 56929671202, 56921814305, 56921851753, 56921859840 };
	auto deletedPidsInfo = get_posts_delete_info(pids);
	for (auto& item : deletedPidsInfo)
	{
		Pval3(item.first, item.second.isDeleted, item.second.monitorType);
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
