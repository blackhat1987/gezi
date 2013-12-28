/** 
 *  ==============================================================================
 * 
 *          \file   test_encode.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2013-12-27 17:08:14.070210
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

TEST(test_encode, func)
{
  string input = "?аидЧ\\?аидЧ\\u0002ел╫У";
  Pval(input);
  Pval(to_utf8(input));
  Pval(to_gbk(to_utf8(input)));
  Pval(to_gbk(to_utf8(boost::erase_all_copy(input,"?"))));
  Pval(to_gbk(to_utf8(boost::erase_all_copy(boost::erase_all_copy(boost::erase_all_copy(input,"?"),""),""))));
  
  Pval(to_gbk(to_utf8(input, UCONV_INVCHAR_IGNORE|UCONV_INVCHAR_GBK_EURO)));
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
