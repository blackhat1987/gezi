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
#include "tieba/feature/urate/UserInfoExtractor.h"
#include "tieba/feature/urate/SundryExtractor.h"
using namespace std;
using namespace gezi;
using namespace gezi::tieba;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(history, "./history", "");
DEFINE_string(i, "./data/pid.txt", "input file");
DEFINE_string(o, "feature.txt", "output file");
DEFINE_int32(nt, 12, "thread num");

inline UrateInfo get_urate_info(uint64 pid, string historyDir)
{
	UrateInfo info;
	string historyFile = historyDir + "/" + STR(pid) + ".xml";
	serialize::load_xml(historyFile, info);
	if (info.postId != pid)
	{
		info = get_urate_info(pid);
		if (info.postId == pid)
		{
			serialize::save_xml(info, historyFile);
		}
	}
	return info;
}

inline Features gen_features(uint64 pid)
{
	Features fe;
	UrateInfo info = get_urate_info(pid, FLAGS_history);
	if (info.postId != pid)
	{
		LOG(WARNING) << "Wrong urate info: " << pid;
		return fe;
	}

	UrateExtractor::info() = move(info);
	FeaturesExtractorMgr mgr;
	mgr.add(new UserInfoExtractor());
	mgr.add(new SundryExtractor());
	mgr.extract(fe);

	return fe;
}

void run()
{
	omp_set_num_threads(FLAGS_nt);
	ofstream ofsFeatures(FLAGS_o);
	AutoTimer timer("run", 0);
	vector<uint64> pids;
	vector<int> labels;
	read_to_vec(FLAGS_i, pids, labels);
	Pval2(pids.size(), pids[0]);

	//----------------先确保写入header
	size_t i = 0;
	for (i = 0; i < pids.size(); i++)
	{
		Features fe = gen_features(pids[i]);
		if (!fe.empty())
		{
			write_table_header(fe, ofsFeatures, "pid");
			write_table(fe, labels[i], ofsFeatures, pids[i]);
			i++;
			break;
		}
	}

#pragma omp parallel for
	for (size_t j = i; j < pids.size(); j++)
	{
		Features fe = gen_features(pids[j]);
#pragma  omp critical 
		{
			write_table(fe, labels[j], ofsFeatures, pids[j]);
		}
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
