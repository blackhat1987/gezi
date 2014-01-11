/** 
 *  ==============================================================================
 * 
 *          \file   test_other.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-01-07 15:48:44.608755
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

DEFINE_int32(logv, 4, "16 debug, 8 trace, 4 online");
DEFINE_string(logdir, "./log", "");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

void run()
{
 Pval((0.0000000001 == 0));
 double val = 0.0;
 Pval((val == 0));
}

int main(int argc, char *argv[])
{
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  int s = google::ParseCommandLineFlags(&argc, &argv, false);
  FLAGS_log_dir = FLAGS_logdir;
  if (FLAGS_logv >= 4)
  {
    FLAGS_stderrthreshold = 0;
  } 
  //  LogHelper log_helper(FLAGS_logv);
  LogHelper::set_level(FLAGS_logv); 

  run();

  return 0;
}
