/** 
 *  ==============================================================================
 * 
 *          \file   test_cpplinq.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-15 07:22:20.380099
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

TEST(cpplinq, func)
{
    vector<int> vec = {1, 2, 3};
    auto vec2 = from(vec) >> select([](int a){return a * 2;}) >> to_vector();
    Pvec(vec2);
}

TEST(cpplinq2, func)
{
    vector<int> vec = {1, 2, 3};
    auto vec2 = from_iterators(vec.begin(), vec.begin()+2) >> select([](int a){return a * 2;}) >> to_vector();
    Pvec(vec2);
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
