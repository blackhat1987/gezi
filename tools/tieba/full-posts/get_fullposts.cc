/** 
 *  ==============================================================================
 * 
 *          \file   get_fullposts.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-20 17:22:16.071814
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define _DEBUG
#define private public
#define protected public
#include "common_util.h"
#include "tieba/get_parsed_info.h"

using namespace std;
using namespace gezi;
using namespace gezi::tieba;
DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_int32(nt, 12, "thread num");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 20, "");
DEFINE_string(i, "./test.data/tid.txt", "input file");
DEFINE_string(history, "./history", "");
DEFINE_string(o, "", "output file");

void run_get_fullposts_info(uint64 tid)
{
	auto info = get_full_posts_info(tid, FLAGS_num, 0, 1);
	string historyPath = FLAGS_history + "/" + STR(tid) + ".json";
	serialize_util::save_json(info, historyPath);
}

void run()
{
	omp_set_num_threads(FLAGS_nt);
	AutoTimer timer("run", 0);
	vector<uint64> tids = read_to_vec<uint64>(FLAGS_i);
	Pval2(tids.size(), tids[0]);
	try_create_dir(FLAGS_history);
#pragma omp parallel for
	for (size_t i = 0; i < tids.size(); i++)
	{
		run_get_fullposts_info(tids[i]);
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
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;
	run();

	return 0;
}
