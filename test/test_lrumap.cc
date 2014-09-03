/** 
 *  ==============================================================================
 * 
 *          \file   test_lrumap.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-03 11:31:46.992181
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "container/LruMap.h"
using namespace std;
using namespace gezi;
DEFINE_int32(vl, 0, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

//淘汰最早进入的key
TEST(lrumap, func)
{
	LruMap<int, string> m(3);
	m[1] = 'a';
	m[2] = 'b';
	m[3] = 'c';
	Pval(m.size());
	for (auto& item : m)
	{
		Pval2(item.first, item.second);
	}
	
	m[4] = 'd';
	Pval(m.size());
	for (auto& item : m)
	{
		Pval2(item.first, item.second);
	}
}

TEST(lruhashmap, func)
{
	LruHashMap<int, string> m(3);
	m[1] = 'a';
	m[2] = 'b';
	m[3] = 'c';
	Pval(m.size());
	for (auto& item : m)
	{
		Pval2(item.first, item.second);
	}

	m[4] = 'd';
	Pval(m.size());
	for (auto& item : m)
	{
		Pval2(item.first, item.second);
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
