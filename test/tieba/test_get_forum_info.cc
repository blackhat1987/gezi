/** 
 *  ==============================================================================
 * 
 *          \file   test_get_forum_info.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-05 15:03:35.627648
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
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(get_forum_id, func)
{
	Pval(get_forum_id("ÎâÒà·²"));
	Pval(get_forum_id("nba"));
	Pval(get_forum_id("ÄÚº­"));
	Pval(get_forum_id("exo")); 
}

TEST(get_forum_ids, func)
{
	auto vec = get_forum_ids(svec({"ÎâÒà·²", "nba", "ÄÚº­", "exo"}));
	Pvec(vec);
}

TEST(get_forum_name, func)
{
	Pval(get_forum_name(46));
	Pval(get_forum_name(711567));
}

TEST(get_forum_names, func)
{
	{
		auto vec = get_forum_names(vector<uint>({ 46, 711567 })); //nba,ÄÚº­
		Pvec(vec);
	}
	{
		auto vec = get_forum_names(vector<uint>({ 711567, 46 })); 
		Pvec(vec);
	}
}

TEST(get_forum_info, func)
{
	{
		ForumInfo info = get_forum_info(46);
		Pval3(info.fid, info.level1Name, info.level2Name);
	}
	{
		ForumInfo info = get_forum_info(711567);
		Pval3(info.fid, info.level1Name, info.level2Name);
	}
}

TEST(get_forums_info, func)
{
	{
		auto vec = get_forums_info(vector<uint>({ 46, 711567 })); //nba,ÄÚº­
		for (auto& info : vec)
		{
			Pval3(info.fid, info.level1Name, info.level2Name);
		}
	}
	{
		auto vec = get_forums_info(vector<uint>({ 711567, 46 }));
		for (auto& info : vec)
		{
			Pval3(info.fid, info.level1Name, info.level2Name);
		}
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
