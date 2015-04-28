/**
 *  ==============================================================================
 *
 *          \file   test_langmodel.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-04-21 10:21:54.797783
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "tools/language_model.h"

using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

void run()
{
	string modelPath = "./data/tieba.5gram.lm";
	PSCONF(modelPath, "LanguageModel");
	PVAL(modelPath);
	int order = 3;
	PSCONF(order, "LanguageModel");
	double oovPunish = -10;
	PSCONF(oovPunish, "LanguageModel");
	const LangModel::AbstractScoreCal& langModel = LangModel::GetModel(LangModel::CalType_SignDict, modelPath.c_str(), order,
		true, true, oovPunish, NULL);

	//TODO FIXME û�е���remove model
	PVAL(langModel.CalSentence("¥ �� �� ��"));
	PVAL(langModel.CalSentence("¥ �� ��"));
	PVAL(langModel.CalSentence("¥ �� �� �� �� �� ѧ ϰ"));
	PVAL(langModel.CalSentence("¥ �� �� �� �� ѧ ϰ"));
	PVAL(langModel.CalSentence("° ± ² ³ ´ µ ¶ · ¸ ¹")); //-49.7
	PVAL(langModel.CalSentence("�� �� �� �� �� �� �� �� �� ��")); // -36.2
	PVAL(langModel.CalSentence("ͼ < �� �� �� �� �� �� �� ��"));
	PVAL(langModel.CalSentence("ͼ �� �� �� �� �� �� �� �� ��"));
	PVAL(langModel.CalSentence("ͼ �� �� �� �� �� �� �� �� ��"));
	PVAL((langModel.CalSentence("ͼ < �� �� �� �� �� �� �� ��") / 10.0));
	PVAL((langModel.CalSentence("ͼ �� �� �� �� �� �� �� ��") / 9.0));
	PVAL((langModel.CalSentence("¥ �� �� �� �� �� ѧ ϰ") / 8.0));
	PVAL((langModel.CalSentence("¥ �� �� �� �� ѧ ϰ") / 7.0));

	PVAL((langModel.CalSentence("� �� �� � �� �� � �� �� � �� �� � �� �� �� �� �� � �� �� � �� �� �� �� �� � �� �� � �� �� � �� �� � � �� �� �") / 41.0));
	PVAL((langModel.CalSentence("ǧ ʫ ֯ �� �� �� �� �� �� �� ̨ ĺ �� �� ֻ �� Ӣ �� �� ޥ �� �� �� �� �� � �� ��") / 28.0));
	PVAL((langModel.CalSentence("�� �� �� �� �� �� �� �� �� ֤ �� �� ¥ �� �� �� ƭ ��") / 18.0));
	PVAL((langModel.CalSentence("�� �� �� �� �� �� �� �� �� �� �� ��") / 12.0));
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
