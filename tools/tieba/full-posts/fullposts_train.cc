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
DEFINE_int32(num, 20, "");
DEFINE_string(history, "./history", "");
DEFINE_string(i, "./test.data/tid.txt", "input file");
DEFINE_string(o, "feature.txt", "output file");
DEFINE_int32(nt, 12, "thread num");

DEFINE_string(urate_history, "./urate.history", "");

inline Features gen_features(uint64 tid)
{
	Features fe;
	FullPostsInfo info = try_get_info<FullPostsInfo>(tid, [](uint64 tid) { return get_full_posts_info(tid, FLAGS_num, 0, 1); }, FLAGS_history);
	if (info.IsValid())
	{
		FullPostsExtractor::info() = move(info);
		FeaturesExtractorMgr mgr;
		add_fullposts_features(mgr);
		mgr.extract(fe);
		{
			UrateInfo uinfo = try_get_info<UrateInfo>(info.pids[0], [](uint64 pid) { return get_urate_info(pid); }, FLAGS_history);
			if (uinfo.IsValid())
			{
				UrateExtractor::info() = move(uinfo);
				FeaturesExtractorMgr mgr;
				add_urate_features(mgr);
				mgr.extract(fe);
			}
			else
			{
				fe.clear();
			}
		}
	}

	return fe;
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


int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	FLAGS_minloglevel = FLAGS_level;
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;
	//SharedConf::init("fullposts_strategy.conf");
	SharedConf::init("urate_strategy.conf");
	run();

	return 0;
}
