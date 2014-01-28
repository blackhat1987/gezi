/** 
 *  ==============================================================================
 * 
 *          \file   select_feature.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-01-22 20:11:40.712156
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <glog/logging.h>
#include <gflags/gflags.h>
#include "common_help.h"
#include "debug_help.h"

using namespace std;
DEFINE_int32(level,0,"min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

DEFINE_bool(use_seg, true, "");

void run()
{

}

int main(int argc, char *argv[])
{
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  int s = google::ParseCommandLineFlags(&argc, &argv, false);
  if (FLAGS_log_dir.empty())
        FLAGS_logtostderr = true;
  FLAGS_minloglevel = FLAGS_level;
  run();

  return 0;
}
