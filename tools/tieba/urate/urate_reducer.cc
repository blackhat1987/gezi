/**
 *  ==============================================================================
 *
 *          \file   urate_reducer.cc
 *
 *        \author   chenghuige
 *
 *          \date   2015-03-03 14:04:33.627047
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


inline void add_urate_features_offline(FeaturesExtractorMgr& mgr)
{
	mgr.add(new SundryExtractor);
	mgr.add(new UserExtractor(false, false));
	mgr.add(new MediaExtractor);
	mgr.add(new NumberExtractor);
	mgr.add(new IpExtractor);
	mgr.add(new TimeExtractor);
	mgr.add(new ForumExtractor(false));
	mgr.add(new TextExtractor);
	mgr.add(new UnusalCnExtractor);
	mgr.add(new UnusalCharExtractor);
	mgr.add(new TextScoreExtractor);
	mgr.add(new TextScoreExtractor("RscTextScore", true));
	mgr.add(new TextScoreExtractor("RocTextScore"));
	
	mgr.add(new TextScoreExtractor("TextScore2"));
	mgr.add(new TextScoreExtractor("RocTextScore2"));
	
	mgr.add(new PlsaTopicExtractor(false)); //解析累加
	mgr.add(new TitleSimExtractor);
	mgr.add(new ContentSimExtractor);
	mgr.add(new LanguageModelExtractor);
	mgr.add(new SequenceExtractor);
	mgr.add(new DictMatchExtractor);
	//mgr.add(new ImgExtractor); //另有专门的reducer处理
}


enum Cols
{
	UID,
	UNAME,
	POST_ID,
	THREAD_ID,
	TIME,
	TITLE,
	CONTENT,
	IP,
	FORUM_ID,
	FORUM_NAME,
	LEVEL1_NAME,
	LEVEL2_NAME,
	DAY,
	HOUR,
	NUM_COLS
};

//info.pids.push_back(UINT64(jsonInfo["post_id"].asString()));
//info.tids.push_back(UINT64(jsonInfo["thread_id"].asString()));
//info.fids.push_back(UINT(jsonInfo["forum_id"].asString()));
//info.fnames.push_back(jsonInfo["forum_name"].asString());
//info.ips.push_back(UINT64(jsonInfo["ip"].asString()));
//info.times.push_back(INT64(jsonInfo["create_time"].asString()));
//info.isThreads.push_back(BOOL(jsonInfo["is_thread"].asString()));
//info.titles.push_back(jsonInfo["title"].asString());
//info.contents.push_back(jsonInfo["content"].asString());
//info.isPostsDeleted.push_back(false); //如果需要通过删帖接口获取
//info.level1Names.push_back("");
//info.level2Names.push_back("");
//info.ranks.push_back(0);
//info.hotValues.push_back(0);

void deal(vector<svec> li)
{
	if (li.empty())
	{
		return;
	}
	try
	{
		UrateInfo info;
		if (li[0].size() != NUM_COLS)
		{
			LOG(INFO) << "wrong.. " << li[0].size() << " " << NUM_COLS;
			for (auto item : li[0])
			{
				LOG(INFO) << item;
			}
			return;
		}
		uint64 uid = UINT64(li[0][UID]);
		string uname = li[0][UNAME];
		uint64 postId = UINT64(li[0][POST_ID]);
		string day = li[0][DAY];
		string hour = li[0][HOUR];
		for (auto l : li)
		{
			try
			{
				auto& postsInfo = info.postsInfo;
				string title = to_gbk(l[TITLE]);
				string content = to_gbk(l[CONTENT]);
				postsInfo.pids.push_back(UINT64(l[POST_ID]));
				postsInfo.tids.push_back(UINT64(l[THREAD_ID]));
				postsInfo.fids.push_back(UINT(l[FORUM_ID]));
				postsInfo.fnames.push_back(l[FORUM_NAME]);
				postsInfo.ips.push_back(UINT64(l[IP]));
				postsInfo.times.push_back(INT64(l[TIME]));
				postsInfo.isThreads.push_back(is_thread(title));
				postsInfo.titles.push_back(title);
				postsInfo.contents.push_back(content);
				postsInfo.level1Names.push_back(to_gbk(l[LEVEL1_NAME]));
				postsInfo.level2Names.push_back(to_gbk(l[LEVEL2_NAME]));
				postsInfo.ranks.push_back(0);
				postsInfo.hotValues.push_back(0);
			}
			catch (...)
			{
				continue;
			}
		}

		info.postId = postId;
		info.postsInfo.userId = uid;
		info.postsInfo.numPosts = info.postsInfo.pids.size();
		info.userInfo.userId = uid;
		info.userInfo.userName = uname;

		Features fe;
		if (info.IsValid())
		{
			UrateExtractor::info() = move(info);
			FeaturesExtractorMgr mgr;
			add_urate_features_offline(mgr);
			mgr.extract(fe);
		}

		cout << uid << "\t" << uname << "\t" << postId << "\t" << fe.Length() << "\t"
			<< fe.str() << "\t" << fe.Str() << "\t"
			<< join(fe.names(), ",") << "\t"
			<< day << "\t" << hour << endl;
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
		if (l.size() != NUM_COLS)
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

	SharedConf::init("urate_reducer.conf");
	run();

	return 0;
}
