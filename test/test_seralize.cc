/** 
 *  ==============================================================================
 * 
 *          \file   test_seralize.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-04-09 20:17:55.412894
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


TEST(test_seralize, func)
{
        {
            ofstream ofs("a.bin", ios::binary);
            int a = 3;
            ofs << 3 << 4.5;
        }
        {
            ifstream ifs("a.bin", ios::binary);
            int a;
            double b;
            ifs >> a >> b;
            Pval2(a, b);
        }
}

TEST(test_seralize2, func)
{
        {
            ofstream ofs("b.bin", ios::binary);
            int a = 3;
            write_elem(a, ofs);
            write_elem(4.5, ofs);
        }
        {
            ifstream ifs("b.bin", ios::binary);
            int a;
            double b;
            read_elem(ifs, a);
            read_elem(ifs, b);
            Pval2(a, b);
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
