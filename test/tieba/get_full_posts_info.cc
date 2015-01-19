/** 
 *  ==============================================================================
 * 
 *          \file   get_full_posts_info.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-01-16 16:05:39.617666
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "tieba/get_info.h"
#include "tieba/info/thread_info.h"

using namespace std;
using namespace gezi;
using namespace gezi::tieba;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf,false, "");
DEFINE_int32(num_floors, 10, "");
DEFINE_string(i, "thread.txt", "input file");
DEFINE_string(o, "", "output file");

DEFINE_string(history, "./history", "");
DEFINE_int32(nt, 12, "thread num");

void get_info(const vector<uint64>& tids)
{
#pragma omp parallel for
	for (size_t i = 0; i < tids.size(); i++)
	{
		try_get_info<FullPostsInfo>(tids[i],
			[&](uint64 tid) { return get_full_posts_info(tid, FLAGS_num_floors, 0, 1); }, FLAGS_history);
	}
}

void run()
{
	try_create_dir(FLAGS_history);
	omp_set_num_threads(FLAGS_nt);

	vector<uint64> tids;
	gezi::read_to_vec(FLAGS_i, tids);
	Pval(tids.size());
	tids = from(tids) >> distinct() >> to_vector();
	Pval(tids.size());
	get_info(tids);
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

	run();

	return 0;
}
