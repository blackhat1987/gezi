/**
 *  ==============================================================================
 *
 *          \file   urate_predicts_from_file.cc
 *
 *        \author   chenghuige
 *
 *          \date   2014-12-13 22:37:38.170303
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
using namespace std;
using namespace gezi;
using namespace gezi::tieba;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

DEFINE_int32(nt, 12, "thread num");

DEFINE_string(history, "./history", "");
DEFINE_string(m, "", "set model path by -m");

void run_predicts_from_file()
{
	ofstream ofs(FLAGS_o);
	vector<uint64> pids;
	gezi::file_to_vec(FLAGS_i, pids);

	SharedPredictors::Instance("model");
	SharedPredictors::Instance("reply.model");
	omp_set_num_threads(FLAGS_nt);
#pragma omp parallel for
	for (size_t i = 0; i < pids.size(); i++)
	{
		uint64 pid = pids[i];
		UrateInfo info;
		Features fe = gen_urate_features(pid, info, FLAGS_history);
		string modelPath = info.nowPostInfo.IsThread() ? "model" : "reply.model";
		if (!FLAGS_m.empty())
		{
			modelPath = FLAGS_m;
		}
		auto& predictor = SharedPredictors::Instance(modelPath);
		double score = predictor->Predict(fe);
		double oriScore = score;
		gezi::tieba::adjust(score, info);
#pragma  omp critical
		ofs << pid << "\t" << info.nowPostInfo.userName << "\t" 
			<< info.nowPostInfo.title << "\t" << gezi::replace(info.nowPostInfo.content, '\n', ' ') << "\t" 
			<< info.nowPostInfo.forumName << "\t" << oriScore << "\t"
			<< score << endl;
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

	SharedConf::init("urate_strategy.conf");
	run_predicts_from_file();

	return 0;
}
