/** 
 *  ==============================================================================
 * 
 *          \file   rstree.cc
 *
 *        \author   chenghuige   
 *
 *          \date   2015-02-05 11:13:45.638368
 *  
 *  \Description:
 *
 *  ==============================================================================
 */

#define private public
#define protected public
#include "common_util.h"
#include "tools/redis/RedisClient.h"
#include "MLCore/PredictorFactory.h"
#include "container/lru_containers.h"
#include "tieba/info/post_info.h"
#include "Rstree.h"
#include "tools/content_process.h"

using namespace std;
using namespace gezi;

DEFINE_int32(vl, 0, "vlog level");
DEFINE_int32(level, 0, "min log level");
DEFINE_string(type, "simple", "");
DEFINE_bool(perf, false, "");
DEFINE_int32(num, 1, "");
DEFINE_string(i, "", "input file");
DEFINE_string(o, "", "output file");

DEFINE_int32(deal_count, 100, "");

DEFINE_string(reply_key, "#!post!#", "");
DEFINE_int32(replys_max_count, 101000, "");//缓存最近10w pid
DEFINE_string(thread_key, "#!thread!#", "");
DEFINE_int32(threads_max_count, 101000, "");//缓存最近10w tid
DEFINE_string(tid_key, "#!tid!#", "");
DEFINE_int32(tids_max_count, 101000, "");//缓存最近10w tid

DEFINE_int32(maxlen, 6, "");
DEFINE_int32(minlen, 2, "");
DEFINE_int32(minfreq, 1000, "");
DEFINE_int32(treesize, 1000000, "");

const int kMaxIds = 1e+5;
LruHashSet<uint64> _visitedIds(kMaxIds);

RedisClient _redisClient;
PredictorPtr _predictor;

Rstree tree(L"#", FLAGS_minlen, FLAGS_maxlen, FLAGS_minfreq, FLAGS_treesize);

void init()
{
	SharedConf::init("fullposts.conf");

	_predictor = PredictorFactory::LoadPredictor("./data/ltrate.thread.model/");

	int redisRet = _redisClient.Init();
	CHECK_EQ(redisRet, 0);
}

void deal(const vector<uint64>& pids)
{
	Pval(pids.size());
	auto infos = tieba::get_posts_info(pids);
	Pval(infos.size());

	for (auto info : infos)
	{
		string content = filter_str(strip_html(info.content));
		if (info.IsThread())
		{
			content = format("{} {}", info.title, content);
		}
		Pval(wstr2str(wstr(content)));
		tree.add(wstr(content));
	}

	Pval(tree.size());
	auto results = tree.find_all_substrs();
	Pval(results.size());
	gezi::sort(results, 10, [](const Rstree::Pair& a, const Rstree::Pair& b) { return a.second > b.second; });
	for (size_t i = 0; i < std::min((int)results.size(), 10) ; i++)
	{
		Pval3(i, wstr2str(results[i].first), results[i].second);
	}
}

void run()
{
	setlocale(LC_ALL, "zh_CN.GB18030");

	init();
	uint64 round = 0;
	vector<uint64> pids;
	while (true)
	{
		svec vec;
		_redisClient.ZrangeFirstNElement(FLAGS_thread_key, 100, vec);
		//_redisClient.ZrangeFirstNElement(FLAGS_reply_key, 1000, vec);
		PVAL2(round, vec.size());
		for (auto& pidStr : vec)
		{
			uint64 pid = UINT64(pidStr);
			if (!_visitedIds.count(pid))
			{
				_visitedIds.insert(pid);
				pids.push_back(pid);
				if (pids.size() == FLAGS_deal_count)
				{
					deal(pids);
					pids.clear();
				}
				PVAL2(round, pid);
			}
		}
		round++;
	}
}

void run2()
{
	//std::locale::global(std::locale(""));
	//string sSource = "gbk字符串";
	//wstring ws = boost::locale::conv::to_utf<wchar_t>(sSource, "GBK");

	//string  ss1 = boost::locale::conv::from_utf(ws, "GBK");

	//Pval2(sSource, ss1);

	//setlocale(LC_ALL, "zh_CN.GB18030");
	std::locale::global(std::locale("zh_CN.GB18030"));

	Rstree tree(L"#");

	tree.set_max_substr_len(FLAGS_maxlen);
	tree.set_min_substr_len(FLAGS_minlen);
	tree.set_min_frequency(FLAGS_minfreq);

	tree.add(wstr("邹红建是垃圾"));
	tree.add(wstr("邹红建不要脸"));
	tree.add(wstr("谁不要脸？"));
	tree.add(wstr("cbg的年终奖为什么不如ecom给力呢?"));
	tree.add(wstr("我也想要50个月的年终奖，！！！"));
	tree.add(wstr("那个叫邹红建的竟然得了5个月年终奖"));
	tree.add(wstr("邹小建是垃圾"));
	tree.add(wstr("邹小建是垃圾"));
	tree.add(wstr("邹小建是垃圾"));

	Pval(tree.find_freq(wstr("不要脸")));
	Pval(tree.find_freq(wstr("邹红建")));
	Pval(tree.find_freq(wstr("年终")));
	Pval(tree.find_freq(wstr("终奖")));
	Pval(tree.find_freq(wstr("邹小建")));
	Pval(tree.find_freq(wstr("红建")));
	Pval(tree.find_freq(wstr("小建")));
	Pval(tree.find_freq(wstr("邹")));

	vector<Rstree::Pair> results = tree.find_all_substrs();

	for (size_t i = 0; i < results.size(); i++)
	{
		Pval3(i, wstr2str(results[i].first), results[i].second);
	}

	for (size_t i = 0; i < tree.size(); i++)
	{
		vector<Rstree::Pair> results = tree.find_substrs(i);
		for (size_t j = 0; j < results.size(); j++)
		{
			Pval4(i, j, wstr2str(results[j].first), results[j].second);
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
	LogHelper::set_level(FLAGS_level);
	if (FLAGS_v == 0)
		FLAGS_v = FLAGS_vl;

	run2();

	run();

	return 0;
}

