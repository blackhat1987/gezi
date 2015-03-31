/** 
 *  ==============================================================================
 * 
 *          \file   test_numeric_limit.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-03-25 10:55:28.533955
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

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

template<typename T>
void run()
{
		Pval(numeric_limits<T>::lowest());
		Pval(numeric_limits<T>::min());
		Pval(numeric_limits<T>::max());
		Pval(numeric_limits<T>::infinity());
		Pval(numeric_limits<T>::epsilon());
		Pval(numeric_limits<T>::quiet_NaN());
		Pval(numeric_limits<T>::round_error());
}

int main(int argc, char *argv[])
{
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  int s = google::ParseCommandLineFlags(&argc, &argv, false);
  if (FLAGS_log_dir.empty())
    FLAGS_logtostderr = true;
  FLAGS_minloglevel = FLAGS_level;
	LogHelper::set_level(FLAGS_level);
  if (FLAGS_v == 0)
    FLAGS_v = FLAGS_vl;

	LOG(INFO) << "int";
  run<int>();
	LOG(INFO) << "uint";
  run<unsigned int>();
	LOG(INFO) << "float";
  run<float>();
	LOG(INFO) << "double";
  run<double>();

  return 0;
}
