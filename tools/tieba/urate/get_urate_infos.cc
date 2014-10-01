/** 
 *  ==============================================================================
 * 
 *          \file   get_urate_infos.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2014-09-09 14:57:50.215366
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "tieba/urate/get_urate_info.h"
using namespace std;
using namespace gezi;
using namespace gezi::tieba;
DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_int32(nt, 12, "thread num");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num, 25, "");
DEFINE_string(i, "./test.data/pid.txt", "input file");
DEFINE_string(history, "./history", "");
DEFINE_string(o, "", "output file");

void run_get_urate_info(uint64 pid)
{
	auto info = get_urate_info(pid, FLAGS_num);
	Pval2_1(info.postId, info.postsInfo.numPosts);
	string historyPath = FLAGS_history + "/" + STR(pid) + ".xml";
	serialize_util::save_xml(info, historyPath);
}

void run()
{
	omp_set_num_threads(FLAGS_nt);
	AutoTimer timer("run", 0);
	vector<uint64> pids;
	read_to_vec(FLAGS_i, pids);
	Pval2(pids.size(), pids[0]);
#pragma omp parallel for
	for (size_t i = 0; i < pids.size(); i++)
	{
		run_get_urate_info(pids[i]);
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
