/** 
 *  ==============================================================================
 * 
 *          \file   test_map_default.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-11-14 08:38:10.556076
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
enum class LoopType
{
	Stochastic,
	BalancedStochastic,
	Roc
};

enum class TrainerType
{
	Pegasos,
	PassiveAggressive,
	MarginPerceptron,
	Romma,
	SgdSVM,
	LeastMeanSquares,
	Logreg,
	LogregPegasos
};

map<string, LoopType> _loopTypes = {
	{ "stochastic", LoopType::Stochastic },
	{ "roc", LoopType::Roc }
};

void run()
{
	Pval(int(_loopTypes["roc"]));
	Pval(int(_loopTypes["stochastic"]));
	Pval(int(_loopTypes["roc2"]));
}

TEST(map_default, func)
{
	run();
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
