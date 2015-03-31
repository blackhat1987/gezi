/**
 *  ==============================================================================
 *
 *          \file   img_reducer.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-03-09 17:28:09.370985
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
#include "tieba/urate/urate_features.h"

using namespace std;
using namespace gezi;
using namespace gezi::tieba;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");


enum Cols
{
	uid, ocr, porn_score, similarity_score, color_score, gameporn_score, textbox_num, text_rate, num_cols
};

void deal(vector<svec> li)
{
	if (li.empty())
	{
		return;
	}
	try
	{
		UrateInfo info;
		if (li[0].size() != num_cols)
		{
			LOG(INFO) << "wrong.. " << li[0].size() << " " << num_cols;
			for (auto item : li[0])
			{
				LOG(INFO) << item;
			}
			return;
		}
		uint64 userid = UINT64(li[0][uid]);
		for (auto l : li)
		{
			try
			{
				auto& imgInfo = info.imginfo;
				imgInfo.color_rate.push_back(INT(l[color_score]));
				imgInfo.gameporn_rate.push_back(INT(l[gameporn_score]));
				imgInfo.ocr_img.push_back(l[ocr]);
				imgInfo.porn_rate.push_back(INT(l[gameporn_score]));
				imgInfo.simi_rate.push_back(INT(l[similarity_score]));
				imgInfo.textbox_num.push_back(INT(l[textbox_num]));
				imgInfo.text_ratio.push_back(INT(l[text_rate]));
				imgInfo.imgCount++;
			}
			catch (...)
			{
				continue;
			}
		}

		Features fe;
		UrateExtractor::info() = move(info);
		FeaturesExtractorMgr mgr;
		mgr.add(new ImgExtractor); //ÐÂÔö
		mgr.extract(fe);

		cout << userid << "\t" << fe.Length() << "\t"
			<< fe.str() << "\t" << fe.Str() << "\t"
			<< join(fe.names(), ",") << endl;
	}
	catch (...)
	{
		LOG(INFO) << li[0][0];
		return;
	}
}

void run()
{
	string line;
	string pre_key = "";
	vector<svec> li;
	while (getline(cin, line))
	{
		svec l = gezi::split(line, '\t');
		if (l.size() != num_cols)
		{
			continue;
		}

		string key = l[0];
		if (key != pre_key)
		{
			if (pre_key != "")
			{
				deal(li);
				li.clear();
			}
			pre_key = key;
		}
		li.push_back(l);
	}

	deal(li);
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

	SharedConf::init("urate_strategy.conf");
	run();

	return 0;
}