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

	//TODO FIXME 没有调用remove model
	PVAL(langModel.CalSentence("楼 主 挽 尊"));
	PVAL(langModel.CalSentence("楼 主 尊"));
	PVAL(langModel.CalSentence("楼 主 挽 尊 好 好 学 习"));
	PVAL(langModel.CalSentence("楼 主 尊 好 好 学 习"));
	PVAL(langModel.CalSentence("掳 卤 虏 鲁 麓 碌 露 路 赂 鹿")); //-49.7
	PVAL(langModel.CalSentence("拎 玲 菱 零 龄 铃 伶 羚 凌 灵")); // -36.2
	PVAL(langModel.CalSentence("图 < 齐 天 下 王 卫 南 北 极"));
	PVAL(langModel.CalSentence("图 文 齐 天 下 王 卫 南 北 极"));
	PVAL(langModel.CalSentence("图 大 齐 天 下 王 卫 南 北 极"));
	PVAL((langModel.CalSentence("图 < 齐 天 下 王 卫 南 北 极") / 10.0));
	PVAL((langModel.CalSentence("图 齐 天 下 王 卫 南 北 极") / 9.0));
	PVAL((langModel.CalSentence("楼 主 挽 尊 好 好 学 习") / 8.0));
	PVAL((langModel.CalSentence("楼 主 尊 好 好 学 习") / 7.0));

	PVAL((langModel.CalSentence("浣 犲 共 娲 伙 紝 浠 栫 帺 锛 屽 弽 涔 嬩 竴 镙 风 殑 銆 傜 疮 浜 嗗 潥 镌 佷 笉 涓 嫔 幓 浜 嗗 氨 鎯 崇 偣 寮 蹇 幂 殑 銆") / 41.0));
	PVAL((langModel.CalSentence("千 诗 织 就 回 文 锦 如 此 阳 台 暮 雨 何 只 有 英 灵 苏 蕙 子 更 无 悔 过 窦 连 波") / 28.0));
	PVAL((langModel.CalSentence("很 多 网 友 的 购 物 经 历 证 明 该 楼 主 是 个 骗 子") / 18.0));
	PVAL((langModel.CalSentence("真 心 分 享 留 下 你 们 的 经 验 呢") / 12.0));
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
