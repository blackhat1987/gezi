/**
 *  ==============================================================================
 *
 *          \file   test_get_url_info.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-07 10:14:48.147212
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

void run()
{
	
}


TEST(get_urls_info, func)
{
	auto infos = get_urls_info(svec({ "http://www.baidu.com", "http://50r.cn/M66mJU", "http://pan.baidu.com/s/1gdlBomJ#dir/path=%2F~%E7%94%B5~%E8%84%91~%E5%92%8C~%E6%89%8B~%E6%9C%BA~%E9%83%BD~%E6%9C%89~%E7%9A%84" }));
	for (auto& info : infos)
	{
		Pval5(info.url, info.rank, info.isJump, info.jumRank, info.content);
	}
	{
		auto infos = get_urls_info(svec({ "http://www.baidu.com", "http://50r.cn/M66mJU" }));
		for (auto& info : infos)
		{
			Pval5(info.url, info.rank, info.isJump, info.jumRank, info.content);
		}
	}
	{
		auto infos = get_urls_info(svec({ "http://50r.cn/M66mJU", "http://www.baidu.com" }));
		for (auto& info : infos)
		{
			Pval5(info.url, info.rank, info.isJump, info.jumRank, info.content);
		}
	}
	{
		auto infos = get_urls_info(svec({ "http://50r.cn/M66mJU", "http://www.qipaqipaqipa", "http://t.cn/RPitksC", "http://t.cn/Rhq2cEO" }));
		for (auto& info : infos)
		{
			Pval5(info.url, info.rank, info.isJump, info.jumRank, info.content);
		}
	}
}

TEST(get_url_info, func)
{
	auto info = get_url_info("http://50r.cn/M66mJU");
	Pval5(info.url, info.rank, info.isJump, info.jumRank, info.content);
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
