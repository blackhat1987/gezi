/** 
 *  ==============================================================================
 * 
 *          \file   test_static_const.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-06-22 20:01:20.676306
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
#include <algorithm>
#include <iostream>

class test
{
        public:
            static const int N = 10;
};


TEST(static_const, func)
{
//http://stackoverflow.com/questions/3025997/defining-static-const-integer-members-in-class-definition
//std::min takes its parameters by const reference. If it took them by value you'd not have this problem but since you need a reference you also need a definition.
//Here's chapter/verse:
//9.4.2/4 - If a static data member is of const integral or const enumeration type, its declaration in the class definition can specify a constant-initializer which shall be an integral constant expression (5.19). In that case, the member can appear in integral constant expressions. The member shall still be defined in a namespace scope if it is used in the program and the namespace scope definition shall not contain an initializer.
        std::cout << test::N << "\n";
        //std::min(9, test::N);
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
