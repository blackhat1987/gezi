/** 
 *  ==============================================================================
 * 
 *          \file   test_bitop.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-04-10 11:37:44.769204
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

void func()
{
	for (int i =-1000; i < 0; i++)
	{
		if (-i - 1 != ~i)
		{
			LOG(WARNING) << i;
		}
	}
}
TEST(bitop, func)
{
		func();
	{
		int node = 2;
		Pval(node);
		Pval((~node));
	}	
	{
		int node = -2;
		Pval(node);
		Pval((~node));
	}
	{
		int node = -3;
		Pval(node);
		Pval((~node));
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
  FLAGS_minloglevel = FLAGS_level;
  boost::progress_timer timer;
  
  return RUN_ALL_TESTS();
}
