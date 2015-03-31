/**
 *  ==============================================================================
 *
 *          \file   test_trate.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-03-14 20:53:26.884014
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#define _DEBUG

#include "common_util.h"
#include "MLCore/PredictorFactory.h"
#include "tieba/info/post_info.h"
#include "Identifer.h"
//#include "MLCore/TextPredictor.h"
#include "tieba/TextPredictor.h"
#include "Predictors/LinearPredictor.h"
using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

DEFINE_int32(type, 0, "");
DEFINE_int64(pid, 0, "");

DEFINE_string(m, "./data/ltrate.thread.model", "");
DEFINE_string(dict, "", "");
DEFINE_bool(hastitle, true, "");

PredictorPtr _predictor;
DoubleIdentifer _identifer;

void init()
{
	SharedConf::init("fullposts.conf");
	_predictor = PredictorFactory::LoadPredictor(FLAGS_m);
	string dictPath = FLAGS_dict.empty() ? FLAGS_m + "/identifer.bin" : FLAGS_dict;
	_identifer.Load(dictPath);
}

void deal(uint64 pid)
{
	auto info = tieba::get_post_info(pid);
	Pval7(info.postId, info.threadId, info.forumName, info.userName, to_time_str(info.createTime), info.title, info.content);
	//double score = FLAGS_hastitle ? TextPredictor::Predict(info.title, info.content, _identifer, _predictor) 
	//	: TextPredictor::Predict(info.title + " " + info.content, _identifer, _predictor);
	Pval(strip_html(info.content));
	double score = FLAGS_hastitle ? gezi::tieba::TextPredictor::Predict(info.title, info.content, _identifer, _predictor)
		: gezi::tieba::TextPredictor::Predict(info.title + " " + info.content, _identifer, _predictor);

	Pval(score);
}

void run()
{
	init();

	if (FLAGS_type != 0)
	{
		uint64 pid;
		while (true)
		{
			cin >> pid;
			deal(pid);
		}
	}
	else
	{
		deal(FLAGS_pid);
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

	run();

	return 0;
}

