/** 
 *  ==============================================================================
 * 
 *          \file   test_static.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-14 11:57:19.126079
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

static int HistoryDays(int days)
{
        static int _days = 30;
        _days = days;
        Pval2(_days, days);
        return _days;
}

TEST(static, func)
{
    Pval(HistoryDays(365));
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
