/**
 *  ==============================================================================
 *
 *          \file   fullposts_train.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-19 22:00:04.452641
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "feature/Features.h"
#include "tieba/get_parsed_info.h"
#include "tieba/fullposts/fullposts_features.h"
#include "tieba/urate/urate_features.h"

using namespace std;
using namespace gezi;
using namespace gezi::tieba;
DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_bool(gf, false, "gen feature");
DEFINE_int32(predict, 0, "1 predict, 2 predicts");
DEFINE_uint64(tid, 0, "");
DEFINE_int32(num, 20, "");
DEFINE_string(history, "./history", "");
DEFINE_string(urate_history, "./urate.history", "");
DEFINE_string(i, "./test.data/tid.txt", "input file");
DEFINE_string(o, "feature.txt", "output file");
DEFINE_int32(nt, 12, "thread num");

Features gen_features(uint64 tid)
{
	return gen_fullposts_features(tid, FLAGS_num, FLAGS_history, FLAGS_urate_history);
}

void run()
{
	try_create_dir(FLAGS_history);
	omp_set_num_threads(FLAGS_nt);

	AutoTimer timer("run", 0);
	vector<uint64> tids;
	vector<int> labels;
	read_to_vec(FLAGS_i, tids, labels);
	Pval2(tids.size(), tids[0]);
	write_features(tids, labels, gen_features, FLAGS_o);
}

void run_gen_feature()
{
	Features fe = gen_features(FLAGS_tid);
	Pval(fe.str());
}

void run_predict()
{
	Features fe = gen_features(FLAGS_tid);
	Pval(fe.str());
	string fullpostsModelPath = "./model";
	PSCONF(fullpostsModelPath, "Global");
	auto& predictor = SharedPredictors::Instance(fullpostsModelPath);
	Pval(predictor->Predict(fe));
}

void run_predicts()
{
	string fullpostsModelPath = "./model";
	PSCONF(fullpostsModelPath, "Global");
	auto& predictor = SharedPredictors::Instance(fullpostsModelPath);
	uint64 tid;
	while (true)
	{
		cin >> tid;
		Pval(tid);
		Features fe = gen_features(tid);
		Pval(fe.str());
		Pval(predictor->Predict(fe));
	}
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
	SharedConf::init("fullposts.conf");

	if (FLAGS_gf)
	{
		run_gen_feature();
	}
	else if (FLAGS_predict == 1)
	{
		run_predict();
	}
	else if (FLAGS_predict == 2)
	{
		run_predicts();
	}
	else
	{ //Ä¬ÈÏÑµÁ·Ä£Ê½
		run();
	}

	return 0;
}
