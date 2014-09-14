/** 
 *  ==============================================================================
 * 
 *          \file   test_conf.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-03-19 14:31:34.014552
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
DEFINE_int32(level, 0, "min log level");
DEFINE_int32(uv, 4, "ulog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(test_conf, func)
{
	string name;
	PSCONF(name, "global");
	Pval(name);
	PSCONF(name, "football");
	Pval(name);
	PSCONF(name, "basketball");
	Pval(name);
	PSCONF(name, "test");
	Pval(name);
	bool ok, ok2;
	PSCONF(ok, "test");
	PSCONF(ok2, "test");
	Pval(ok);
	Pval(ok2);
}

//TEST(name_exist, func)
//{
//	string nameExist = "meixi";
//	SCONF(nameExist);
//	Pval(nameExist);
//}
//
//TEST(name_non_exist, func)
//{
//	string nameNonExist = "jordan";
//	SCONF(nameNonExist);
//	Pval(nameNonExist);
//}

TEST(test_conf, perf)
{
	string name2 = "meixi_default";
	for (size_t i = 0; i < 1000; i++)
	{
		PSCONF(name2, "football");
	}
	Pval(name2);
}

TEST(test_conf, perf2)
{
	string name = "jordan_default";
	for (size_t i = 0; i < 1000; i++)
	{
		PSCONF(name, "football");
	}
	Pval(name);
}


TEST(test_conf_double, perf)
{
	double ratio2 = 0.1982;
	for (size_t i = 0; i < 1000; i++)
	{
		PSCONF(ratio2, "football");
	}
	Pval(ratio2);
}

TEST(test_conf_double, perf2)
{
	double ratio = 0.1982;
	for (size_t i = 0; i < 1000; i++)
	{
		PSCONF(ratio, "football");
	}
	Pval(ratio);
}

TEST(test_conf_double, perf3)
{
	double ratio3 = 0.1982;
	for (size_t i = 0; i < 1000; i++)
	{
		PSCONF(ratio3, "football");
	}
	Pval(ratio3);
}

TEST(test_conf_double, perf4)
{
	double ratio4 = 0.1982;
	for (size_t i = 0; i < 1000; i++)
	{
		PSCONF(ratio4, "football");
	}
	Pval(ratio4);
}

//TEST(test_conf_bool, perf)
//{
//	bool use = false;
//	for (size_t i = 0; i < 1000; i++)
//	{
//		PSCONF(use, "football");
//	}
//	Pval(use);
//}
//
//TEST(test_conf_bool, perf2)
//{
//	bool use2 = false;
//	for (size_t i = 0; i < 1000; i++)
//	{
//		PSCONF(use2, "football");
//	}
//	Pval(use2);
//}
//
//TEST(test_conf_bool, perf3)
//{
//	bool use3 = false;
//	for (size_t i = 0; i < 1000; i++)
//	{
//		PSCONF(use3, "football");
//	}
//	Pval(use3);
//}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	FLAGS_minloglevel = FLAGS_level;
	LogHelper::set_level(FLAGS_uv);
	SharedConf::init("test_conf.conf");
	return RUN_ALL_TESTS();
}
