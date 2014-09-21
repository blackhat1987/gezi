/** 
 *  ==============================================================================
 * 
 *          \file   test_const.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-18 10:36:13.695313
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

struct Node
{
  int a = 3;
  int constA = 5;
};

void Predict(Node& node)
{
    Pval(node.a);
}

void Predict(const Node& node)
{
    Pval(node.constA);        
}

double test()
{
    int a = 3;
    int b = 2;
    return a = b;
}

map<string, int> m;
int& test2()
{
    return m["abc"] = 4;
}

TEST(const, func)
{
    Node node;
    Predict(node);
    Predict(Node());
    Pval(test);
    auto& x = test2();
    Pval(x);
    x = 128;
    Pval(m["abc"]);
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