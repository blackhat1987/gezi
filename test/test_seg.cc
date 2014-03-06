/** 
 *  ==============================================================================
 * 
 *          \file   test_seg.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-03-05 18:12:09.186445
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "word_seg.h"
using namespace std;
using namespace gezi;
DEFINE_int32(level, 0, "min log level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

TEST(test_seg, func)
{
	seg_init2();
	Pval(segment2("我爱你中国速去郭美美吧查看", "|"));
	Pval(segment2("今天天气不错百度贴吧欢迎你", "|"));
	seg_init();
	Pval(segment("我爱你中国速去郭美美吧查看", "|"));
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
