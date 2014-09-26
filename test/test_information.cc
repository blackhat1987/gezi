/** 
 *  ==============================================================================
 * 
 *          \file   test_informaiton.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-23 10:00:02.858434
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"

using namespace std;
using namespace gezi;
DEFINE_int32(vl, 5, "vlog level");
DEFINE_string(i, "", "input");
DEFINE_string(o, "", "output");
DEFINE_string(type, "simple", "");

void run()
{

}

TEST(informaiton, func)
{
        {
            ivec vec = {1, 2, 3, 4};
            Pval(information(vec));
        }
        {
            ivec vec = {1, 1, 2, 2};
            Pval(information(vec));
        }
        {
            ivec vec = {1, 2, 3, 4, 5, 6, 7, 8};
            Pval(information(vec));
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
