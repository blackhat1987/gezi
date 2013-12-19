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
  string s = "��������·�Ͽ�����������ˤ���ڽ��ϣ����ܹ�ȥ�������̷��������������������Ҫ���£������Ź���Ҫ��թ��Ǯ���ҹ����ȵ��أ��ڵ��ϲ�ͣ�ĳ鴤���ҿ��°�ĭ��������һ�´��ˣ��ұ߳鴤���䶯������䶯������֮�⣬վ�������Ļ����ˣ������̻����ԭ�ط���������ع�������p��Ѧ��p��Ѧ��fp��Ѧ��l��騡�ona��l��騡�q��";
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
