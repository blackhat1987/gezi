/**
 *  ==============================================================================
 *
 *          \file   trate_predicts.cc
 *
 *        \author   chenghuige
 *
 *          \date   2016-03-14 15:20:43.157787
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
//#define _DEBUG

#include "common_util.h"
#include "MLCore/PredictorFactory.h"
#include "Identifer.h"
#include "MLCore/TextPredictor.h"

using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

DEFINE_string(m, "./models/trate.model", "");

PredictorPtr _predictor;
DoubleIdentifer _identifer;

void init()
{
	_predictor = PredictorFactory::LoadPredictor(FLAGS_m);
	_identifer.Load(FLAGS_m + "/identifer.bin");
}

string deal(string content)
{
	content = gezi::strip_html(content);
	if(content.length() > 100)
		content = gezi::gbk_substr(content, 0, 100);
	content = content + " " + gezi::normalize_str(content);
	return content;
}

void run()
{
	string line;
	ifstream ifs(FLAGS_i);
	while (getline(ifs, line))
	{
		auto l = gezi::split(line, '\t');

		string pid = l[0];
		string title = l[1];
		string content = l[2];
		Pval(pid);
		Pval(title);
		Pval(content);
		title = deal(title);
		content = deal(content);
		Pval(title);
		Pval(content);
		double score = TextPredictor::Predict(title, content, _identifer, _predictor);
		Pval(score);
	}
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

	init();

	run();

	return 0;
}
