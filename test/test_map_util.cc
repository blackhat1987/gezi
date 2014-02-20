/** 
 *  ==============================================================================
 * 
 *          \file   test_map_util.cc
 *
 *        \author   gezi   
 *
 *          \date   2014-02-17 18:04:27.268644
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public


#include "map_util.h"
#include "common_util.h"
using namespace std;
using namespace gezi;

DEFINE_string(type, "simple", "");


TEST(get_value, func)
{
	map<string, int> m = { { "chg", 1 }, { "meixi", 2 }, { "jordan", 3 } };
	Pval(get_value(m, "chg", 0));
	Pval(get_value(m, "kobe", 0));
	double val = m.count("chg") ? m["chg"] : 0;
	Pval(val);
	val = m.count("kobe") ? m["kobe"] : 0;
	Pval(val);
}

int main(int argc, char *argv[])
{
  FLAGS_logtostderr = true;
  testing::InitGoogleTest(&argc, argv); 
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  int s = google::ParseCommandLineFlags(&argc, &argv, false);
  boost::progress_timer timer;
  return RUN_ALL_TESTS();
}
