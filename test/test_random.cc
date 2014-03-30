/** 
 *  ==============================================================================
 * 
 *          \file   test_random.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-03-30 13:37:29.869194
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "random_util.h"
using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(test_random, func)
{
	vector<Int> vec = cpplinq::range(10) >> to_vector();
	Pvec(vec);
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
