/**
 *  ==============================================================================
 *
 *          \file   lou_reducer.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-03-10 14:55:01.368167
 *
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"

#include "feature/Features.h"
#include "tieba/get_parsed_info.h"
#include "tieba/fullposts/fullposts_features.h"
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
	thread_id, create_time, uid, uname, ip, title, content, num_cols
};

void deal(vector<svec> li)
{
	if (li.empty())
	{
		return;
	}
	try
	{
		FullPostsInfo info;
		string title_ = to_gbk(li[0][title]);
		if (!is_thread(title_))
		{ //表示比如当前天的数据里 虽然有这个thread id 但是对应是之前某天发的 不予考虑
			return;
		}
		info.title = title_;
		uint64 tid = UINT64(li[0][thread_id]);
		uint64 userId = UINT64(li[0][uid]);
		for (auto l : li)
		{
			try
			{
				info.uids.push_back(UINT(l[uid]));
				info.unames.push_back(l[uname]);
				info.ips.push_back(UINT64(l[ip]));
				info.contents.push_back(to_gbk(l[content]));
			}
			catch (...)
			{
				continue;
			}
		}

		Features fe;
		FullPostsExtractor::info() = move(info);
		FeaturesExtractorMgr mgr;
		add_fullposts_features(mgr);
		mgr.extract(fe);

		cout << tid << "\t" << userId << "\t" << fe.Length() << "\t"
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

	//SharedConf::init("urate_strategy.conf");
	run();

	return 0;
}
