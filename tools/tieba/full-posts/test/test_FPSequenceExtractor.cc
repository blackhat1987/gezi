/**
 *  ==============================================================================
 *
 *          \file   test_FPSequenceExtractor.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-07-14 11:15:40.635750
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "tieba/feature/fullposts/SequenceExtractor.h"
#include "tieba/fullposts/fullposts_features.h"

using namespace std;
using namespace gezi;
using namespace gezi::tieba;

DEFINE_int32(vl, 3, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 10, "");
DEFINE_uint64(tid, 0, "3889607299");
DEFINE_string(i, "", "");
DEFINE_string(o, "", "output file");

void run()
{
	Features fe;
	uint64 tid = FLAGS_tid;
	FullPostsInfo info = try_get_info<FullPostsInfo>(tid,
		[&](uint64 tid) { return get_full_posts_info(tid, FLAGS_num, 0, 1); }, "./history");
	if (info.IsValid())
	{
		FullPostsExtractor::info() = move(info);
		FeaturesExtractorMgr mgr;
		mgr.add(new FPSequenceExtractor);
		mgr.extract(fe);
	}
	Pval(fe.Str());
}

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv[0]);
	google::InstallFailureSignalHandler();
	google::SetVersionString(get_version());
	int s = google::ParseCommandLineFlags(&argc, &argv, false);
	if (FLAGS_log_dir.empty())
		FLAGS_logtostderr = true;
	FLAGS_minloglevel = FLAGS_level;
	//LogHelper::set_level(FLAGS_level);
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;

	run();

	return 0;
}
