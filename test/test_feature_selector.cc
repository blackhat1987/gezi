/** 
 *  ==============================================================================
 * 
 *          \file   test_feature_selector.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-01-19 19:24:39.834785
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "feature/FeatureSelector.h"
using namespace std;
using namespace gezi;

DEFINE_int32(logv, 4, "16 debug, 8 trace, 4 online");
DEFINE_string(logdir, "./log", "");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "result.txt", "output file");

void run(FeatureSelector& fs)
{
  LOG(INFO) << "MAX";
  fs = fs.strategy(FeatureSelector::MAX);
  fs.calc();
  fs.save(cout, -1, 0);
  fs.save(cout, -1, 1);
  fs.save(cout, -1, -1);

  LOG(INFO) << "AVG";
  fs = fs.strategy(FeatureSelector::AVG);
  fs.calc();
  fs.save(cout, -1, -1);

  LOG(INFO) << "SUM";
  fs = fs.strategy(FeatureSelector::SUM);
  fs.calc();
  fs.save(cout, -1, -1);
}

void run()
{
  using namespace collocation;
  Pval((0 * log(0)));
  FeatureSelector fs;
  //  fs.add("��\t��\t�ٶȴ���", 0);
  //  fs.add("��\t��\t��˼����", 1);
  //  fs.add("����\t��\t�ٶȴ���", 0);
  //  fs.add("����\t����\t��˼����", 1);
  //  fs.add("��˼����\t��\tʳ��\t�ܲ", 0);
  //  fs.add("��˼����\t̫Զ", 1);
  //  fs.add("�ܲ", 1);
  //  
  //  run(fs.method(CHI));
  //  run(fs.method(IG));
  //  run(fs.method(MI));
  //  run(fs.method(MI2));
  //  run(fs.method(PMI));
  //  run(fs.method(ECE));

  fs.clear();
  fs.add("ʳ��\t�ٶȴ���", 0);
  fs.add("��Ů\t�ٶȴ���", 0);
  fs.add("ʳ��\t��˼����", 1);
  fs.add("�೵\t��˼����", 1);
  

  Pvec(fs._classCounts);
  Pvec(fs._featureCounts);
  
  foreach(vector<int>& vec, fs._counts)
  {
    Pvec(vec);
  }

  run(fs.method(CHI));
  run(fs.method(IG));
	fs.save("temp.txt");
  run(fs.method(MI));
  run(fs.method(MI2));
  run(fs.method(PMI));
  run(fs.method(ECE));

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
