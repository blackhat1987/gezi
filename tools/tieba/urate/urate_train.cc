/**
 *  ==============================================================================
 *
 *          \file   urate_train.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-09 22:26:08.809415
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public

#include "common_util.h"
#include "feature/Features.h"
#include "tieba/urate/get_urate_info.h"
#include "tieba/urate/urate_features.h"
#include "Predictors/GbdtPredictor.h"
using namespace std;
using namespace gezi;
using namespace gezi::tieba;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(history, "./history", "");
DEFINE_string(i, "./test.data/pid.txt", "input file");
DEFINE_string(o, "feature.txt", "output file");
DEFINE_int32(nt, 12, "thread num");

DEFINE_int32(index, 0, "id index");
DEFINE_int32(index2, 1, "label index");

DEFINE_uint64(pid, 0, "");
DEFINE_bool(gf, false, "gen feature");
DEFINE_int32(predict, 0, "1 predict, 2 predicts, 3 predicts from file");
DEFINE_string(m, "model", "model path");

Features gen_features(uint64 pid)
{
	return gen_urate_features(pid, FLAGS_history);
}

void run()
{
	try_create_dir(FLAGS_history);
	omp_set_num_threads(FLAGS_nt);
	
	AutoTimer timer("run", 0);
	vector<uint64> pids;
	vector<int> labels;
	read_to_vec(FLAGS_i, pids, labels, FLAGS_index, FLAGS_index2);
	Pval2(pids.size(), pids[0]);
	write_features(pids, labels, 
		[&](uint64 pid) { return gen_urate_features(pid, FLAGS_history); }, FLAGS_o);
}

void run_gen_feature()
{
	Features fe = gen_features(FLAGS_pid);
	Pval(fe.str());
}

void run_predict()
{
	Features fe = gen_features(FLAGS_pid);
	Pval(fe.str());
	string modelPath = FLAGS_m;
	auto& predictor = SharedPredictors::Instance(modelPath);
	Pval(predictor->Predict(fe));
}

void run_predicts()
{
	string modelPath = FLAGS_m;
	auto& predictor = SharedPredictors::Instance(modelPath);
	//auto predictor = PredictorFactory::LoadPredictor(modelPath);
	uint64 pid;
	while (true)
	{
		cin >> pid;
		Pval(pid);
		Features fe = gen_features(pid);
		Pval2(fe.size(), fe.str());
		Pval(predictor->Predict(fe));
	}
}

void run_predicts_from_file()
{
	ifstream ifs(FLAGS_i);
	string line;
	while (getline(ifs, line))
	{
		uint64 pid = UINT64(line);
		UrateInfo info;
		Features fe = gen_urate_features(pid, info, FLAGS_history);
		string modelPath = info.nowPostInfo.IsThread() ? "model" : "reply.model";
		auto& predictor = SharedPredictors::Instance(modelPath);
		double score = predictor->Predict(fe);
		gezi::tieba::adjust(score, info);
	}
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	LogHelper::set_level(FLAGS_level);
	FLAGS_minloglevel = FLAGS_level;
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;
	SharedConf::init("urate_strategy.conf");

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
	else if (FLAGS_predict == 3)
	{
		run_predicts_from_file();
	}
	else
	{ //Ä¬ÈÏÑµÁ·Ä£Ê½
		run();
	}

	return 0;
}
