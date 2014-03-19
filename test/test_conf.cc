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

TEST(test_conf, perf)
{
	string name2;
	PSCONF(name2, "football");
}

TEST(test_conf, perf2)
{
	string name;
	PSCONF(name, "football");
}

int main(int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  int s = google::ParseCommandLineFlags(&argc, &argv, false);
  if (FLAGS_log_dir.empty())
    FLAGS_logtostderr = true;
  FLAGS_minloglevel = FLAGS_level;
  boost::progress_timer timer;
	SharedConf::init("test_conf.conf");
  return RUN_ALL_TESTS();
}
