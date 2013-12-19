/** 
 *  ==============================================================================
 * 
 *          \file   test_content_filter.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2013-12-18 15:58:54.939908
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

DEFINE_int32(logv, 16, "16 debug, 8 trace, 4 online");
DEFINE_string(logdir, "./log", "");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

void run()
{
  string s = "今天在马路上看到个老奶奶摔倒在街上，我跑过去把老奶奶扶起来，结果看样子她又要倒下，我想着估计要讹诈我钱，我果断先倒地，在地上不停的抽搐并且口吐白沫，老奶奶一下呆了，我边抽搐边蠕动，大概蠕动到两米之外，站起来拍拍灰走了，老奶奶还愣在原地发呆。我深藏功与名。p┰薛ぉp┰薛ぉfp┰薛ぉlс楱∩onaねlс楱∩q×";
  Pval(s);
  Pval(filter_str(s));
  Pval(extract_chinese(s));
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
